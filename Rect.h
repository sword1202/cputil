//
// Created by Semyon Tikhonenko on 6/11/18.
//

#ifndef CPPUTILSTESTS_RECT_H
#define CPPUTILSTESTS_RECT_H

#include "Point.h"

namespace CppUtils {

    template<typename T>
    struct Rect {
        Point<T> A;
        T width;
        T height;

        Rect(T x, T y, T width, T height) : A(x, y), width(width), height(height) {}
        Rect(const Point<T> &A, T width, T height) : A(A), width(width), height(height) {}
        Rect() = default;

        bool containsPoint(T x, T y) const {
            return x >= A.x && x <= A.x + width && y >= A.y && y <= A.y + height;
        }

        bool containsPoint(const Point<T>& point) const {
            return containsPoint(point.x, point.y);
        }

        void translate(T x, T y) {
            A.translate(x, y);
        }

        Point<T> getB() {
            return Point<T>(A.x + width, 0);
        }

        Point<T> getC() {
            return Point<T>(A.x + width, A.y + height);
        }

        Point<T> getD() {
            return Point<T>(0, A.y + height);
        }
    };

    typedef Rect<float> RectF;
}


#endif //CPPUTILSTESTS_RECT_H
