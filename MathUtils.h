//
// Created by Semyon Tikhonenko on 6/8/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_MATH_H
#define VOCALTRAINER_MATH_H

#include <cmath>

namespace CppUtils {

    namespace Math {
        template<typename Float>
        Float MakePositiveAngle(Float angle) {
            if (angle < 0) {
                return M_PI * 2 + angle;
            }

            return angle;
        }

        template<typename Float>
        bool IsAngleBetweenAngles(Float mid, Float start, Float end) {
            mid = MakePositiveAngle(mid);

            end = (end - start) < 0.0f ? end - start + M_PI * 2 : end - start;
            mid = (mid - start) < 0.0f ? mid - start + M_PI * 2 : mid - start;
            return mid < end;
        }

        template<typename Float>
        bool IsInClosedInterval(Float a, Float b, Float value) {
            if (a > b) {
                std::swap(a, b);
            }

            return value >= a && value <= b;
        }
    }
}


#endif //VOCALTRAINER_MATH_H
