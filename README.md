# TableModifyEvent
Mysql Database notifies java application when a record has changed.

Requirements:
Java 8

Run Steps :
1) Generate the header file :
$ /usr/lib/jvm/jdk1.8.0_92/bin/javah  -classpath ./:../lib/jna/jna.jar:../lib/rabbitmq/rabbitmq-client-2.8.4.jar -jni my.test.TableEventReader

2) Rename generated header File

$ mv my_test_TableEventReader.h TableEventReader.h

3) create tme.so
$ gcc -o tme.so -shared -Wl,-soname,libnative.so -I/usr/lib/jvm/jdk1.8.0_92/include -I/usr/lib/jvm/jdk1.8.0_92/include/linux tme.c -static -lc

#if above fails , try running below 

$ gcc -o tme.so -shared -Wl,-soname,libnative.so -I/usr/lib/jvm/jdk1.8.0_92/include -I/usr/lib/jvm/jdk1.8.0_92/include/linux tme.c -lc -fPIC

gcc $(mysql_config --cflags) -I/usr/lib/jvm/jdk1.8.0_92/include -I/usr/lib/jvm/jdk1.8.0_92/include/linux -shared -fPIC -o db_modify_event.so db_modify_event.c

4) Copy db_modify_event.so to Mysql plugin directory

5) Then on mysql prompt  execute ->
      drop function IF EXISTS db_modify_event ;  
      CREATE FUNCTION db_modify_event RETURNS INT SONAME 'db_modify_event.so'; 
      select db_modify_event('topic','data');
6) Check is function created or not using -> select * from mysql.func;"

7) Copy tme.so to /var/tmp/MYSQL_UDF  

8) Add the above path to tomcat in its init script as 
