# SQLITE_OPEN_SHARED_SCHEMA
- 在同一个进程内，对于version_schema相同的数据库复用内存，可以大大减小内存。

## SQLITE_ENABLE_IOTRACE

## foreign_keys

## SQLite打开文件支持中文路径
- 调查如何支持的

# sqlite线程模式的设置
(1)编译阶段

这几种模式可以通过参数SQLITE_THREADSAFE在编译阶段指定，可以取值0，1，2，默认是1。这三种取值的含义如下：

0:单线程模式，即内部不做mutex保护，多线程运行sqlite不安全。

1:多线程的串行模式，sqlite帮助多线程实现串行化。

2:多线程的并发模式，要求同一个时刻，同一个连接不被多个线程使用。

(2)打开数据库阶段     

除了可以在编译阶段指定运行模式，还可以在打开数据库时(sqlite3_open_v2())通过参数指定，主要的几个参数以及含义如下：

SQLITE_OPEN_NOMUTEX: 设置数据库连接运行在多线程模式(没有指定单线程模式的情况下)

SQLITE_OPEN_FULLMUTEX：设置数据库连接运行在串行模式。

SQLITE_OPEN_SHAREDCACHE：设置运行在共享缓存模式。

SQLITE_OPEN_PRIVATECACHE：设置运行在非共享缓存模式。

SQLITE_OPEN_READWRITE：指定数据库连接可以读写。

SQLITE_OPEN_CREATE：如果数据库不存在，则创建。

(3)运行时阶段

通过调用sqlite3_config接口，也可以设置运行模式。

若编译参数SQLITE_THREADSAFE=1 or SQLITE_THREADSAFE=2，那么可以在运行时设置线程模式。

SQLITE_CONFIG_SINGLETHREAD：单线程模式

SQLITE_CONFIG_MULTITHREAD：多线程模式，应用层保证同一个时刻，同一个连接只有一个线程使用。

SQLITE_CONFIG_SERIALIZED：串行模式，sqlite帮助多线程实现串行化。

 

http://www.cnblogs.com/cchust/p/4738002.html

 

Configuring The SQLite Library

int sqlite3_config(int, ...);

The sqlite3_config() interface is used to make global configuration changes to SQLite in order to tune SQLite to the specific needs of the application. The default configuration is recommended for most applications and so this routine is usually not necessary. It is provided to support rare applications with unusual needs.

The sqlite3_config() interface is not threadsafe. The application must ensure that no other SQLite interfaces are invoked by other threads while sqlite3_config() is running.

The sqlite3_config() interface may only be invoked prior to library initialization using sqlite3_initialize() or after shutdown by sqlite3_shutdown(). If sqlite3_config() is called after sqlite3_initialize() and before sqlite3_shutdown() then it will return SQLITE_MISUSE. Note, however, that sqlite3_config() can be called as part of the implementation of an application-defined sqlite3_os_init().

 

https://sqlite.org/c3ref/config.html

 

启动时指定线程模式

int(
  filename     sqlite3 ppDb           flags                zVfs        );
在这个函数中，flags可以指定线程模式，还可以指定其他的配置。

flags的第一部分必须是下面三个之一：

1. SQLITE_OPEN_READONLY

2. SQLITE_OPEN_READWRITE

3. SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE

第二部分可以选择 SQLITE_OPEN_NOMUTEX， SQLITE_OPEN_FULLMUTEX，SQLITE_OPEN_SHAREDCACHE，SQLITE_OPEN_PRIVATECACHE或 SQLITE_OPEN_URI。

SQLITE_OPEN_NOMUTEX，选择multi-thread线程模式
SQLITE_OPEN_FULLMUTEX，进入serialized线程模式。
 

这几工作需要，用到sqlite多线程功能，这几天研究了一下，验证了一下结果，供大家参考：

1、如果是SQLITE_OPEN_FULLMUTEX，也就是串行化方式，则对于连接时互斥的，只有一个连接关闭，另外一个连接才能读写

2、如果是SQLITE_OPEN_NOMUTEX，则是多线程模式，对于写是互斥的，但是如果一个连接持续写，另外一个连接是无法写入的，只能是错误或者超时返回。不过一个连接写，多个连接读，是没问题的。windows版本模式是SQLITE_OPEN_NOMUTEX


The sqlite3_open_v2() interface works like sqlite3_open() except that it accepts two additional parameters for additional control over the new database connection. The flags parameter to sqlite3_open_v2() can take one of the following three values, optionally combined with the SQLITE_OPEN_NOMUTEX, SQLITE_OPEN_FULLMUTEX, SQLITE_OPEN_SHAREDCACHE, SQLITE_OPEN_PRIVATECACHE, and/or SQLITE_OPEN_URI flags:

 

SQLITE_OPEN_READONLY

The database is opened in read-only mode. If the database does not already exist, an error is returned.

 

 

SQLITE_OPEN_READWRITE

The database is opened for reading and writing if possible, or reading only if the file is write protected by the operating system. In either case the database must already exist, otherwise an error is returned.

 

 

SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE

The database is opened for reading and writing, and is created if it does not already exist. This is the behavior that is always used for sqlite3_open() and sqlite3_open16().

 

If the 3rd parameter to sqlite3_open_v2() is not one of the combinations shown above optionally combined with other SQLITE_OPEN_* bits then the behavior is undefined.

If the SQLITE_OPEN_NOMUTEX flag is set, then the database connection opens in the multi-thread threading mode as long as the single-thread mode has not been set at compile-time or start-time. 

If the SQLITE_OPEN_FULLMUTEX flag is set then the database connection opens in the serialized threading mode unless single-thread was previously selected at compile-time or start-time. 

The SQLITE_OPEN_SHAREDCACHE flag causes the database connection to be eligible to use shared cache mode, regardless of whether or not shared cache is enabled using sqlite3_enable_shared_cache(). 

The SQLITE_OPEN_PRIVATECACHE flag causes the database connection to not participate in shared cache mode even if it is enabled.

 

 

https://sqlite.org/c3ref/open.html

# 
## Parallel read and write in SQLite
https://www.skoumal.com/en/parallel-read-and-write-in-sqlite/

##
- PRAGMA journal_mode=MEMORY

# test
const char* gddbpath = NULL;
    ret = liosport_outputs_get("gddb", &gddbpath);
    if (ret) {
        ret = -1;
        liosport_eventlog(LIOSPORT_EVENTLOG_FETAL, "Can not get output gddb!");
        return ret;
    }

    
   // SQLITE_API sqlite3_backup* sqlite3_backup_init(
   //     sqlite3 * pDest,                        /* Destination database handle */
   //     const char* zDestName,                 /* Destination database name */
   //     sqlite3 * pSource,                      /* Source database handle */
   //     const char* zSourceName                /* Source database name */
            
    clock_t start, end;


    start = clock();
    std::string destPath = "file::memory:";
    std::string destDbName = gd::PoiDatabase::getDatabaseBaseName();
    sqlite3* pDest = NULL;
    int nRet = sqlite3_open_v2(destPath.c_str(), &pDest, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    
  
    char* szError = 0;
    std::string sql = "ATTACH \':memory:\' as " + destDbName;

    nRet = sqlite3_exec(pDest, sql.c_str(), 0, 0, &szError);

    sql = " PRAGMA " + destDbName + ".page_size  = 32768 ";
    nRet = sqlite3_exec(pDest, sql.c_str(), 0, 0, &szError);

    sql = " PRAGMA " + destDbName + ".cache_size  = 30000 ";
    nRet = sqlite3_exec(pDest, sql.c_str(), 0, 0, &szError);

    sql = " PRAGMA " + destDbName + ".synchronous  = OFF ";
    nRet = sqlite3_exec(pDest, sql.c_str(), 0, 0, &szError);


    const char* szMessage = sqlite3_errmsg(pDest);
   
    std::string sourceDBName = gd::PoiDatabase::getDatabaseName();
    std::string sourcePath = std::string(gddbpath) + sourceDBName;
    sqlite3* pSource = NULL;
    nRet = sqlite3_open_v2(sourcePath.c_str(), &pSource, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    sqlite3_backup*  backup = sqlite3_backup_init(pDest, destDbName.c_str(),pSource,"main");

    const char* szMessage1 = sqlite3_errmsg(pDest);
   

    int  nPage = 0;
   
    nRet =  sqlite3_backup_step(backup, -1);
   
    nPage = sqlite3_backup_pagecount(backup);

    // nRet = sqlite3_backup_remaining(sqlite3_backup * p);
     
    nPage = sqlite3_backup_pagecount(backup);
    nRet = sqlite3_backup_finish(backup);
    end = clock();

   
    printf("%d\n", (end - start));
    start = clock();
    CppSQLite3::Database poiDB(pDest);

    gd::PoiLayer::Reader r(poiDB);
    for (; r.hasFeature(); r.nextFeature()) {
        gd::PoiLayer::Feature f;
        r.getFeature(f);
    }
    end = clock();
    printf("%d\n", (end - start));
    return ret;