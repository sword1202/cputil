//
// Created by Semyon Tikhonenko on 11/23/17.
//

#include <stdio.h>  /* defines FILENAME_MAX */
#include <memory>
#include <string>
#ifdef __APPLE__
#include <unistd.h>
#define GetCurrentDir getcwd
#else
#include <direct.h>
#define GetCurrentDir _getcwd
#endif

namespace CppUtils {
    namespace System {
        bool getWorkingDirectory(std::string* out) {
            char cCurrentPath[FILENAME_MAX];

            if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) {
                return false;
            }

            out->assign(cCurrentPath);
            return true;
        }
    }
}
