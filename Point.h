//
// Created by Semyon Tikhonenko on 6/7/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_POINT_H
#define VOCALTRAINER_POINT_H

#include "HashUtils.h"
#include "Primitives.h"

namespace CppUtils {

    template<typename T>
    struct Point {
        T x;
        T y;

        Point() : x(0), y(0) {

        }

        Point(T x, T y) : x(x), y(y) {

        }

        bool operator==(const Point &rhs) const {
            return Primitives::CompareFloats(x, rhs.x) &&
                    Primitives::CompareFloats(y, rhs.y);
        }

        bool operator!=(const Point &rhs) const {
            return !(rhs == *this);
        }

        bool compareUsingEpsilon(const Point<T>& other, T epsilon) const {
            return Primitives::CompareFloatsUsingEpsilon(x, other.x, epsilon)
                    && Primitives::CompareFloatsUsingEpsilon(y, other.y, epsilon);
        }
    };

    typedef Point<float> PointF;
    typedef Point<double> PointD;
}

MAKE_HASHABLE_TEMPLATE1(CppUtils::Point, t.x, t.y)


#endif //VOCALTRAINER_POINT_H
