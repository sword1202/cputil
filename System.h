//
// Created by Semyon Tikhonenko on 11/23/17.
//

#ifndef CPP_SYSTEM_H
#define CPP_SYSTEM_H

#include <string>
#include "config.h"

namespace CppUtils {
namespace System {
    CPP_UTILS_DLLHIDE bool getWorkingDirectory(std::string* out);
}
}

#endif //CPP_SYSTEM_H
