//
// Created by Semyon Tikhonenko on 6/7/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_LINE_H
#define VOCALTRAINER_LINE_H

#include "Point.h"
#include "GeometryUtils.h"

namespace CppUtils {

    template<typename T>
    struct Line {
        Point<T> A;
        Point<T> B;

        Line(const Point<T> &A, const Point<T> &B) : A(A), B(B) {
        }

        Line(T x1, T y1, T x2, T y2) : A(x1, y1), B(x2, y2) {

        }

        Line() {
        }

        bool intersects(const Line<T>& other) const {
            return GeometryUtils::GetLinesIntersection(A.x, A.y, B.x, B.y, other.A.x,
                    other.A.y, other.B.x, other.B.y, nullptr, nullptr);
        }

        bool getIntersection(const Line<T>& other, Point<T>* outIntersection) const {
            return GeometryUtils::GetLinesIntersection(A.x, A.y, B.x, B.y, other.A.x,
                    other.A.y, other.B.x, other.B.y, &outIntersection->x, &outIntersection->y);
        }

        bool operator==(const Line<T> &rhs) const {
            return A == rhs.A &&
                    B == rhs.B;
        }

        bool operator!=(const Line<T> &rhs) const {
            return !(rhs == *this);
        }
    };

    typedef Line<float> LineF;
    typedef Line<double> LineD;
}


#endif //VOCALTRAINER_LINE_H
