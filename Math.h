//
// Created by Semyon Tikhonenko on 6/8/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_MATH_H
#define VOCALTRAINER_MATH_H

#include <math.h>

namespace CppUtils {

    namespace Math {
        template<typename Float>
        bool isAngleBetweenAngles(Float mid, Float start, Float end) {
            end = (end - start) < 0.0f ? end - start + M_PI * 2 : end - start;
            mid = (mid - start) < 0.0f ? mid - start + M_PI * 2 : mid - start;
            return mid < end;
        }
    }
}


#endif //VOCALTRAINER_MATH_H
