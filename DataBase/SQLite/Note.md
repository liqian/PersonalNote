# SQLITE_OPEN_SHARED_SCHEMA
- 在同一个进程内，对于version_schema相同的数据库复用内存，可以大大减小内存。

## SQLITE_ENABLE_IOTRACE

## foreign_keys

## SQLite打开文件支持中文路径
- 调查如何支持的


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