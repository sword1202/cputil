//
// Created by Semyon Tikhonenko on 11/23/17.
//

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
#include <direct.h>
    #define GetCurrentDir _getcwd
#else
#include <unistd.h>
#include <memory>
#include <string>

#define GetCurrentDir getcwd
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
