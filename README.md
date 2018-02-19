# TableModifyEvent
Mysql Database notifies java application when a record has changed.

Requirements:
Java 8

Ubuntu 14.04 or greater 

Run Steps :
1) Generate the header file :

$ /usr/lib/jvm/jdk1.8.0_92/bin/javah  -classpath ./:../lib/jna/jna.jar:../lib/rabbitmq/rabbitmq-client-2.8.4.jar -jni my.test.TableEventReader

2) Rename generated header File

$ mv my_test_TableEventReader.h TableEventReader.h

3) create tme.so

$ gcc -o tme.so -shared -Wl,-soname,libnative.so -I/usr/lib/jvm/jdk1.8.0_92/include -I/usr/lib/jvm/jdk1.8.0_92/include/linux tme.c -static -lc

#if above fails , try running below 

$ gcc -o tme.so -shared -Wl,-soname,libnative.so -I/usr/lib/jvm/jdk1.8.0_92/include -I/usr/lib/jvm/jdk1.8.0_92/include/linux tme.c -lc -fPIC

4) create db_modify_event.so

$ gcc $(mysql_config --cflags) -I/usr/lib/jvm/jdk1.8.0_92/include -I/usr/lib/jvm/jdk1.8.0_92/include/linux -shared -fPIC -o db_modify_event.so db_modify_event.c

5) Copy db_modify_event.so to Mysql plugin directory

6) Then on mysql prompt  execute :

      drop function IF EXISTS db_modify_event ;  
      
      CREATE FUNCTION db_modify_event RETURNS INT SONAME 'db_modify_event.so';
      
      select db_modify_event('topic','data');

7) Check is function created or not using -> select * from mysql.func;

8) Copy tme.so to /var/tmp/MYSQL_UDF  

9) Add the above path to tomcat in its init script as 
  
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/var/tmp/MYSQL_UDF
  
