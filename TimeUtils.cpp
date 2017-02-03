//
// Created by Semyon Tikhonenko on 1/11/17.
// Copyright (c) 2017 Mac. All rights reserved.
//

#include <chrono>
#include "TimeUtils.h"

using namespace std::chrono;

namespace Azazai {
namespace TimeUtils {
    int64_t nowInMicroseconds() {
        return duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count();
    }
}
}