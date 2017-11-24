//
// Created by Semyon Tikhonenko on 7/27/17.
//

#ifndef CALMNESSSCORE_JNIJniUTFString_H
#define CALMNESSSCORE_JNIJniUTFString_H


#include <jni.h>

namespace ECM { namespace CalmnessScore {

    class JniUTFString {
        jstring string;
        const char *data = nullptr;
        JNIEnv *env;
    public:
        JniUTFString(jstring string, JNIEnv *env);

        const char *getData();

        jint length() const;

        ~JniUTFString();
    };
}}


#endif //CALMNESSSCORE_JNIJniUTFString_H
