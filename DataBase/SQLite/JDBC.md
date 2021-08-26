The issue exists since SQLiteJDBC-3.22.0, not exist before SQLiteJDBC-3.22.0.

When I run my executable jar, there is an issue:
```
Exception in thread "main" java.lang.reflect.InvocationTargetException
	at sun.reflect.NativeMethodAccessorImpl.invoke0(Native Method)
	at sun.reflect.NativeMethodAccessorImpl.invoke(NativeMethodAccessorImpl.java:62)
	at sun.reflect.DelegatingMethodAccessorImpl.invoke(DelegatingMethodAccessorImpl.java:43)
	at java.lang.reflect.Method.invoke(Method.java:498)
	at org.springframework.boot.loader.MainMethodRunner.run(MainMethodRunner.java:49)
	at org.springframework.boot.loader.Launcher.launch(Launcher.java:107)
	at org.springframework.boot.loader.Launcher.launch(Launcher.java:58)
	at org.springframework.boot.loader.JarLauncher.main(JarLauncher.java:88)
Caused by: java.lang.ExceptionInInitializerError
	at org.sqlite.SQLiteDataSource.getConnection(Unknown Source)
	at org.sqlite.SQLiteDataSource.getConnection(Unknown Source)
	at org.apache.tomcat.jdbc.pool.PooledConnection.connectUsingDataSource(PooledConnection.java:256)
	at org.apache.tomcat.jdbc.pool.PooledConnection.connect(PooledConnection.java:210)
	at org.apache.tomcat.jdbc.pool.ConnectionPool.createConnection(ConnectionPool.java:744)
	at org.apache.tomcat.jdbc.pool.ConnectionPool.borrowConnection(ConnectionPool.java:676)
	at org.apache.tomcat.jdbc.pool.ConnectionPool.getConnection(ConnectionPool.java:198)
	at org.apache.tomcat.jdbc.pool.DataSourceProxy.getConnection(DataSourceProxy.java:131)
	at com.mxnavi.dbc_mxlive.DumpManager.build(DumpManager.java:55)
	at com.mxnavi.dbc_mxlive.DumpManager.main(DumpManager.java:105)
	... 8 more
Caused by: java.lang.NullPointerException
	at java.io.File.<init>(File.java:277)
	at java.util.jar.JarFile.<init>(JarFile.java:103)
	at org.sqlite.SQLiteJDBCLoader.getNativeLibraryPackageNames(Unknown Source)
	at org.sqlite.SQLiteJDBCLoader.extractNativeLibrariesFromPackage(Unknown Source)
	at org.sqlite.SQLiteJDBCLoader.initialize(Unknown Source)
	at org.sqlite.JDBC.<init>(Unknown Source)
	at org.sqlite.JDBC.<clinit>(Unknown Source)
	... 18 more
```

```SQLite-3.36.0
Caused by: java.lang.NullPointerException
	at java.io.File.<init>(File.java:277)
	at java.util.jar.JarFile.<init>(JarFile.java:103)
	at org.sqlite.NdsJDBCLoader.getNativeLibraryPackageNames(NdsJDBCLoader.java:151)
	at org.sqlite.NdsJDBCLoader.extractNativeLibrariesFromPackage(NdsJDBCLoader.java:132)
	at org.sqlite.NdsJDBCLoader.extractAndLoadLibraryFile(NdsJDBCLoader.java:48)
	at org.sqlite.SQLiteJDBCLoader.loadSQLiteNativeLibrary(SQLiteJDBCLoader.java:216)
	at org.sqlite.SQLiteJDBCLoader.initialize(SQLiteJDBCLoader.java:67)
	at org.sqlite.core.NativeDB.load(NativeDB.java:63)
	at org.sqlite.SQLiteConnection.open(SQLiteConnection.java:240)
	... 22 more

```

```new snapshot
Caused by: java.lang.Exception: No native library found for os.name=Linux, os.arch=x86_64, paths=[/org/sqlite/native/Linux/x86_64:/usr/java/packages/lib/amd64:/usr/lib64:/lib64:/lib:/usr/lib]
	at org.sqlite.SQLiteJDBCLoader.loadSQLiteNativeLibrary(SQLiteJDBCLoader.java:238)
	at org.sqlite.SQLiteJDBCLoader.initialize(SQLiteJDBCLoader.java:67)
	at org.sqlite.core.NativeDB.load(NativeDB.java:63)
	at org.sqlite.SQLiteConnection.open(SQLiteConnection.java:240)
	... 22 more

```


```
private static List<String> getNativeLibraryPackageNames(String var0) throws IOException, URISyntaxException {
        ArrayList var1 = new ArrayList();
        URL var2 = SQLiteJDBCLoader.class.getProtectionDomain().getCodeSource().getLocation();

        //debug test info
        System.out.println(var2.toString());

        JarFile var3 = new JarFile(var2.toURI().getPath());
        Enumeration var4 = var3.entries();

        while(var4.hasMoreElements()) {
            JarEntry var5 = (JarEntry)var4.nextElement();
            if (!var5.isDirectory()) {
                String var6 = "/" + var5.getName();
                if (var6.contains(var0)) {
                    var1.add(var6);
                }
            }
        }

        var3.close();
        return var1;
    }


jar:file:/home/liqian/Workspace/gitlab/dump_mxlive/target/dump_mxlive-1.0-SNAPSHOT.jar!/BOOT-INF/lib/sqlitejdbc-3.22.0-2.jar!/
```

dump_mxlive-1.0-SNAPSHOT.jar is the executable jar, its structure:
----BOOT-INF
    ----classes
    ----lib
        ----sqlitejdbc-3.22.0-2.jar
----META-INF
----org
    ----springframework