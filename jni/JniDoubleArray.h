//
// Created by Semyon Tikhonenko on 7/27/17.
//

#ifndef CPPUTILS_JNIFLOATARRAY_H
#define CPPUTILS_JNIFLOATARRAY_H


#include <jni.h>
#include "../config.h"

namespace CppUtils {

    class CPP_UTILS_DLLHIDE JniDoubleArray {
        jdoubleArray javaArray;
        jdouble *data = nullptr;
        JNIEnv *env;
    public:
        JniDoubleArray(jdoubleArray javaArray, JNIEnv *env);

        jdouble *getData();

        jint length() const;

        ~JniDoubleArray();
    };
}


#endif //CPPUTILS_JNIFLOATARRAY_H
