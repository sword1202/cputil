#include <jni.h>
#include "JniUtils.h"

namespace CppUtils { namespace JniUtils {

    jdoubleArray NewJavaArray(JNIEnv *env, const double *array, jsize size) {
        jdoubleArray result = env->NewDoubleArray(size);
        env->SetDoubleArrayRegion(result, 0, size, array);
        return result;
    }

    void ThrowRuntimeException(JNIEnv *env, const char *message) {
        jclass exception = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(exception, message);
    }

}}
