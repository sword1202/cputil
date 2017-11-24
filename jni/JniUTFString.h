//
// Created by Semyon Tikhonenko on 7/27/17.
//

#ifndef CPPUTILS_JNIJniUTFString_H
#define CPPUTILS_JNIJniUTFString_H


#include <jni.h>
#include "../config.h"

namespace CppUtils {

    class CPP_UTILS_DLLHIDE JniUTFString {
        jstring string;
        const char *data = nullptr;
        JNIEnv *env;
    public:
        JniUTFString(jstring string, JNIEnv *env);

        const char *getData();

        jint length() const;

        ~JniUTFString();
    };
}


#endif //CPPUTILS_JNIJniUTFString_H
