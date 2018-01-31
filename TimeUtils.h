//
// Created by Semyon Tikhonenko on 1/11/17.
// Copyright (c) 2017 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_TIMEUTILS_H
#define VOCALTRAINER_TIMEUTILS_H


#include <cstdint>
#include "config.h"

namespace CppUtils {
namespace TimeUtils {
#ifdef __APPLE__
	CPP_UTILS_DLLHIDE int64_t NowInMicroseconds();
#else
	int64_t NowInMicroseconds();
#endif
}
}


#endif //VOCALTRAINER_TIMEUTILS_H
