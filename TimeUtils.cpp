//
// Created by Semyon Tikhonenko on 1/11/17.
// Copyright (c) 2017 Mac. All rights reserved.
//

#include <chrono>
#include "TimeUtils.h"

using namespace std::chrono;

namespace CppUtils {
namespace TimeUtils {
    int64_t NowInMicroseconds() {
        return duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count();
    }

    double NowInSeconds() {
        return NowInMicroseconds() / 1000000.0;
    }
}
}