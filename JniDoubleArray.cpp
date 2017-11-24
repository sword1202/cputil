//
// Created by Semyon Tikhonenko on 7/27/17.
//

#include "JniDoubleArray.h"
#include <assert.h>

namespace ECM { namespace CalmnessScore {


JniDoubleArray::JniDoubleArray(jdoubleArray javaArray, JNIEnv *env) : javaArray(javaArray),
                                                                   env(env) {}
JniDoubleArray::~JniDoubleArray() {
    if (data) {
        env->ReleaseDoubleArrayElements(javaArray, data, 0);
        data = nullptr;
    }
}

jdouble *JniDoubleArray::getData() {
    assert(!data);
    data = env->GetDoubleArrayElements(javaArray, nullptr);
    return data;
}

jint JniDoubleArray::length() const {
    return env->GetArrayLength(javaArray);
}


}}
