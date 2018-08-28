//
// Created by Semyon Tikhonenko on 1/11/17.
// Copyright (c) 2017 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_TIMEUTILS_H
#define VOCALTRAINER_TIMEUTILS_H


#include <cstdint>
#include "config.h"
#include <iostream>
#include <unordered_map>
#include <string>

namespace CppUtils {
namespace TimeUtils {
	CPP_UTILS_DLLHIDE int64_t NowInMicroseconds();
	CPP_UTILS_DLLHIDE double NowInSeconds();

	template <typename Func, typename Stream = std::ostream>
	void LogExecutionTime(const char* label, Func func, Stream& os = std::cout) {
		auto now = NowInMicroseconds();
		func();
		auto diff = NowInMicroseconds() - now;
		os<<label<<" = "<<diff<<"\n";
	}

	namespace {
	    std::unordered_map<std::string, int64_t> times;
	}

	template <typename Char>
    void LogExecutionTimeStart(const Char* label) {
        times[label] = NowInMicroseconds();
	}

    template <typename Stream = std::ostream>
    void LogExecutionTimeEnd(const char* label, Stream& os = std::cout) {
        int64_t now = NowInMicroseconds();
        auto before = times[label];
        auto diff = now - before;
        os<<label<<" = "<<diff<<"\n";
    }

    struct ExecuteTimeLoggerGuard {
	    std::string label;
	    std::ostream& os;

        ExecuteTimeLoggerGuard(const char* label, std::ostream& os = std::cout);
        ~ExecuteTimeLoggerGuard();
	};
}
}


#endif //VOCALTRAINER_TIMEUTILS_H
