/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class my_test_TableEventReader */

#ifndef _Included_my_test_TableEventReader
#define _Included_my_test_TableEventReader
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     my_test_TableEventReader
 * Method:    read_message
 * Signature: (ILmy/test/TableEvent;J)V
 */
JNIEXPORT void JNICALL Java_my_test_TableEventReader_read_1message
  (JNIEnv *, jclass, jint, jobject, jlong);

/*
 * Class:     my_test_TableEventReader
 * Method:    get_message_qid
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_my_test_TableEventReader_get_1message_1qid
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
