//
// Created by Semyon Tikhonenko on 6/8/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_OPENGLUTILS_H
#define VOCALTRAINER_OPENGLUTILS_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <string>

namespace CppUtils {

    namespace OpenGLUtils {
        GLuint LoadShaders(const char* vertexShader, const char* fragmentShader);
    }
}


#endif //VOCALTRAINER_OPENGLUTILS_H
