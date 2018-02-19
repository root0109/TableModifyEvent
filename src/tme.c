#define MAX_TOPIC_SIZE 256
#define MAX_DATA_SIZE 2048
#define QUEUE_PATH "/var/tmp"
#include <sys/ipc.h>
#include <sys/msg.h>
#include <jni.h>
#include <string.h>
#include "TableEventReader.h"

typedef struct 
{
    long msgType;                /* Message type */
	char topic[MAX_TOPIC_SIZE];	 /* Event Topic */
    char data[MAX_DATA_SIZE];	 /* Event Data */
} TableEvent;

//key_t is actually just a long
key_t get_message_key()
{
	return ftok(QUEUE_PATH, 'm');
}

int open_queue(key_t keyval)
{
     int qid;
     if((qid = msgget(keyval, IPC_CREAT | 0666 )) == -1)
     {
         return(-1);
     }
     return(qid);
}

int send_message(int qid, TableEvent *event)
{
     int result, length;
     length = sizeof(TableEvent) - sizeof(long);
     if((result = msgsnd(qid, (TableEvent *) event, length, IPC_NOWAIT)) == -1)
     {
         return(-1);
     }
     return(result);
}

void read_message(int qid, TableEvent *event, long type)
{
     event->msgType = type;
	 int length = sizeof(TableEvent) - sizeof(long);
     msgrcv(qid, (TableEvent *) event, length, type, 0);
}

JNIEXPORT jint JNICALL Java_my_test_TableEventReader_get_1message_1qid(JNIEnv *env, jclass clazz)
{
	return open_queue(get_message_key());
}

JNIEXPORT void JNICALL Java_my_test_TableEventReader_read_1message(JNIEnv *env, jclass clazz, jint qId, jobject event, jlong msgType)
{
    TableEvent tableEvent;
	tableEvent.msgType = 1;
	read_message(qId, (TableEvent *) &tableEvent, msgType);
	jclass jClassEvent = (*env)->GetObjectClass(env, event);
	jfieldID dataFieldId =  (*env)->GetFieldID(env, jClassEvent, "data", "Ljava/lang/String;");
	jfieldID topicFieldId =  (*env)->GetFieldID(env, jClassEvent, "topic", "Ljava/lang/String;");
	jstring jstrData = (*env)->NewStringUTF(env, tableEvent.data);
	jstring jstrTopic = (*env)->NewStringUTF(env, tableEvent.topic);
	(*env)->SetObjectField(env, event, dataFieldId, jstrData);
	(*env)->SetObjectField(env, event, topicFieldId, jstrTopic);
}
