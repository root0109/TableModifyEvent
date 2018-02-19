#ifdef STANDARD
/* STANDARD is defined, don't use any mysql functions */
   #include <stdlib.h>
   #include <stdio.h>
   #include <string.h>
   #ifdef __WIN__
   	typedef unsigned __int64 ulonglong;/* Microsofts 64 bit types */
	   typedef __int64 longlong;
   #else
	   typedef unsigned long long ulonglong;
	   typedef long long longlong;
   #endif /*__WIN__*/
#else
   #include <my_global.h>
   #include <my_sys.h>
   #if defined(MYSQL_SERVER)
 	  #include <m_string.h>/* To get strmov() */
   #else
   /* when compiled as standalone */
	   #include <string.h>
	   #define strmov(a,b) stpcpy(a,b)
	   #define bzero(a,b) memset(a,0,b)
	   #define memcpy_fixed(a,b,c) memcpy(a,b,c)
   #endif
#endif /* STANDARD */
#include <mysql.h>
#include <ctype.h>
#ifdef HAVE_DLOPEN
#include "tme.c"
   /* These must be right or mysqld will not find the symbol! */
   my_bool db_modify_event_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
   
   void db_modify_event_deinit(UDF_INIT *initid );
   
   longlong db_modify_event(UDF_INIT* initid, UDF_ARGS* args , char* is_null, char* error);
   
   my_bool db_modify_event_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
   {
     if(!args->arg_count == 2 || !args->arg_type[0] == STRING_RESULT || !args->arg_type[1] == STRING_RESULT) {
       strcpy(message, "Expected 2 string arguments (topic, data)");
       return 1;
     }
     initid->maybe_null=1;
     return 0;
   }
   
   /**************************************************************************** 
   ** Deinit function. This should free all resources allocated by
   ** this function.
   ** Arguments:
   ** initid	Return value from xxxx_init
   ****************************************************************************/
   void db_modify_event_deinit(UDF_INIT *initid)
   {
 	  
   }
   
   /***************************************************************************
   ** UDF long long function.
   ** Arguments:
   ** initid	Return value from xxxx_init
   ** args		The same structure as to xxx_init. This structure
   **		contains values for all parameters.
   **		Note that the functions MUST check and convert all
   **		to the type it wants!  Null values are represented by
   **		a NULL pointer
   ** is_null	If the result is null, one should store 1 here.
   ** error	If something goes fatally wrong one should store 1 here.
   **
   ** This function should return the result as a long long
   ***************************************************************************/
   longlong db_modify_event(UDF_INIT* initid, UDF_ARGS* args, char* is_null , char* error)
   {
     char *topic=args->args[0];
     char *data=args->args[1];
     /* Generate IPC key value */
     key_t msgkey = get_message_key();
     int qId = open_queue(msgkey);
     TableEvent event;
     event.msgType = 1;
     strcpy(event.topic, topic);
     strcpy(event.data, data);
     /* Shoot message! */
     return send_message(qId, (TableEvent *) &event);
   }
   
#endif /* HAVE_DLOPEN */