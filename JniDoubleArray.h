//
// Created by Semyon Tikhonenko on 7/27/17.
//

#ifndef CALMNESSSCORE_JNIFLOATARRAY_H
#define CALMNESSSCORE_JNIFLOATARRAY_H


#include <jni.h>

namespace ECM { namespace CalmnessScore {

    class JniDoubleArray {
        jdoubleArray javaArray;
        jdouble *data = nullptr;
        JNIEnv *env;
    public:
        JniDoubleArray(jdoubleArray javaArray, JNIEnv *env);

        jdouble *getData();

        jint length() const;

        ~JniDoubleArray();
    };
}}


#endif //CALMNESSSCORE_JNIFLOATARRAY_H
