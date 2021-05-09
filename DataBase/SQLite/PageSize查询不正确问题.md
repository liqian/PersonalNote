
# 现象：
C++、java 或者shell，在刚打开SQLite数据连接的时候，如果执行SQL:
```
pragma page_size
```
返回的值是Default page size(以前是1024，当前最新是4096)，并不是数据库真实的page size.

NDS DevKit has default page size 4096 bytes from version 3.12.0.

# 原因：
Default page size (1024) is reported until SQLite client reads first page from the database. 

Please try to do a SQL SELECT statement before 'pragma page_size'.

# 建议方式：
I would recommend to use:

SELECT 1 FROM sqlite_master

This command "touches" the databases with minimal effort (A SELECT * FROM sqlite_master would also be possible).

The sqlite_master table is a special table which exists in any SQLite database.

# 例如：
```shell
nds_sqlite.exe RELOCATE.NDS

sqlite> pragma page_size;
4096
sqlite> select 1 from sqlite_master;

sqlite > pragma page_size;
65536
```

以下为C++和java的伪代码：
```java
String aQuery = "PRAGMA page_size ";
Connection acon;

PreparedStatement aStatement = aConnection.prepareStatement(aQuery);
ResultSet aResultSet = aStatement.executeQuery();
int pageSize = aResultSet.getInt((1));//default page size 4096
```

```java 
String aQuery = "select 1 from sqlite_master ";
Connection acon;

PreparedStatement aStatement = aConnection.prepareStatement(aQuery);
ResultSet aResultSet = aStatement.executeQuery();

//
String aQuery = "PRAGMA page_size ";
Connection acon;

PreparedStatement aStatement = aConnection.prepareStatement(aQuery);
ResultSet aResultSet = aStatement.executeQuery();
int pageSize = aResultSet.getInt((1));//page size is correct.

```