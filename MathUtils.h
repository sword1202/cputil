//
// Created by Semyon Tikhonenko on 6/8/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_MATH_H
#define VOCALTRAINER_MATH_H

#include <cmath>
#include "Primitives.h"
#include <assert.h>

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

        template<typename Number>
        Number SelectValueFromRangeProjectedInRange(Number value,
                                                    Number fromRangeBegin, Number fromRangeEnd,
                                                    Number inRangeBegin, Number inRangeEnd) {
            assert(value >= fromRangeBegin);
            assert(value <= fromRangeEnd);

            double k = double(inRangeEnd - inRangeBegin) / (fromRangeEnd - fromRangeBegin);
            return Number((value - fromRangeBegin) * k + inRangeBegin);
        }

        inline int RoundToInt(float f) {
            return int(roundf(f));
        }

        inline int RoundToInt(double d) {
            return int(round(d));
        }

        inline short RoundToShort(double d) {
            int value = RoundToInt(d);
            assert(value <= std::numeric_limits<short>::max() && value >= std::numeric_limits<short>::min());
            return static_cast<short>(value);
        }

        inline unsigned char RoundToUnsignedChar(double d) {
            int value = RoundToInt(d);
            assert(value <= std::numeric_limits<unsigned char>::max() && value >= std::numeric_limits<unsigned char>::min());
            return static_cast<unsigned char>(value);
        }

        inline double FindNearestDividable(double value, double denominator) {
            double _;
            double k = modf(value / denominator, &_);
            if (k < 0.5) {
                return value - denominator * k;
            } else {
                return value + denominator * (1 - k);
            }
        }

        template <typename In, typename Result>
        Result CutIfOutOfClosedRange(In value, Result min, Result max) {
            if (value < min) {
                return min;
            }

            if (value > max) {
                return max;
            }

            return value;
        }
    }
}


#endif //VOCALTRAINER_MATH_H
