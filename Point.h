//
// Created by Semyon Tikhonenko on 6/7/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_POINT_H
#define VOCALTRAINER_POINT_H

#include <ostream>
#include "HashUtils.h"
#include "Primitives.h"
#ifdef __OBJC__
#import <CoreGraphics/CoreGraphics.h>
#endif

namespace CppUtils {

    template<typename T>
    struct Point {
        T x;
        T y;

        Point() : x(0), y(0) {

        }

        Point(T x, T y) : x(x), y(y) {

        }

#ifdef __OBJC__
        Point(const CGPoint& cgPoint) : x(cgPoint.x), y(cgPoint.y) {
        }
#endif

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

        T sqrDistanceTo(const Point<T>& to) const {
            return (to.x - x) * (to.x - x) + (to.y - y) * (to.y - y);
        }

        T distanceTo(const Point<T>& to) const {
            return (T)sqrt(sqrDistanceTo(to));
        }

        Point<T> operator-(const Point<T>& anotherPoint) {
            return Point<T>(x - anotherPoint.x, y - anotherPoint.y);
        }

        Point<T>& operator-=(const Point<T>& anotherPoint) {
            translate(anotherPoint.x, anotherPoint.y);
            return *this;
        }

        Point<T> operator+(const Point<T>& anotherPoint) {
            return Point<T>(x + anotherPoint.x, y + anotherPoint.y);
        }

        void translate(T x, T y) {
            this->x += x;
            this->y += y;
        }

        Point<T> translatedBy(T x, T y) const {
            return Point<T>(this->x + x, this->y + y);
        }

        friend std::ostream &operator<<(std::ostream &os, const Point &point) {
            os << "x: " << point.x << " y: " << point.y;
            return os;
        }
    };

    typedef Point<float> PointF;
    typedef Point<double> PointD;
}

MAKE_HASHABLE_TEMPLATE1(CppUtils::Point, t.x, t.y)


#endif //VOCALTRAINER_POINT_H
