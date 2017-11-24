#ifndef SLEEPALGORITHMANDROID_JNIUTILS_H
#define SLEEPALGORITHMANDROID_JNIUTILS_H

#include <jni.h>

namespace ECM { namespace CalmnessScore { namespace JniUtils {
    jdoubleArray NewJavaArray(JNIEnv* env, const double* array, jsize size);
    void ThrowRuntimeException(JNIEnv* env, const char *message);
}}}

#endif //SLEEPALGORITHMANDROID_JNIUTILS_H
