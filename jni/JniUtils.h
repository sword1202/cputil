#ifndef SLEEPALGORITHMANDROID_JNIUTILS_H
#define SLEEPALGORITHMANDROID_JNIUTILS_H

#include <jni.h>
#include "../config.h"

namespace CppUtils {
    namespace JniUtils {
        CPP_UTILS_DLLHIDE jdoubleArray NewJavaArray(JNIEnv* env, const double* array, jsize size);
        CPP_UTILS_DLLHIDE void ThrowRuntimeException(JNIEnv* env, const char *message);
    }
}

#endif //SLEEPALGORITHMANDROID_JNIUTILS_H
