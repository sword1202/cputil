//
// Created by Semyon Tikhonenko on 7/27/17.
//

#include <assert.h>
#include "JniUTFString.h"

namespace ECM { namespace CalmnessScore {


JniUTFString::JniUTFString(jstring string, JNIEnv *env) : string(string),
                                                           env(env) {}
JniUTFString::~JniUTFString() {
    if (data) {
        env->ReleaseStringUTFChars(string, data);
        data = nullptr;
    }
}

const char *JniUTFString::getData() {
    assert(!data);
    data = env->GetStringUTFChars(string, nullptr);
    return data;
}

jint JniUTFString::length() const {
    return env->GetStringLength(string);
}


}}
