//
// Created by Semyon Tikhonenko on 1/11/17.
// Copyright (c) 2017 Mac. All rights reserved.
//

#include <chrono>
#include "TimeUtils.h"
#include "StringUtils.h"
#include <string>

using namespace std::chrono;

static int64_t start = duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count();

namespace CppUtils {
namespace TimeUtils {
    // Use this to calculate intervals
    int64_t NowInMicrosecondsSinceStart() {
        return duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count() - start;
    }

    std::string NowInMicrosecondsInPrettyFormat() {
        int64_t now = NowInMicrosecondsSinceStart();
        std::string result;
        auto microSec = now % 1000;
        auto milliSec = (now / 1000) % 1000;
        auto seconds = now / 1000000;

        return Strings::ToString(seconds, ',', milliSec, ',', microSec);
    }

    // Use this to calculate intervals
    double NowInSecondsSinceStart() {
        return NowInMicrosecondsSinceStart() / 1000000.0;
    }

    int64_t NowInMicrosecondsSince1970() {
        return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
    }

    double NowInSecondsSince1970() {
        int64_t now = NowInMicrosecondsSince1970();
        return now / 1000000.0;
    }

    ExecuteTimeLoggerGuard::ExecuteTimeLoggerGuard(const char* label, std::ostream& os) : os(os) {
        this->label = label;
        LogExecutionTimeStart(label);
    }

    ExecuteTimeLoggerGuard::~ExecuteTimeLoggerGuard() {
        LogExecutionTimeEnd(label.data(), os);
    }
}
}