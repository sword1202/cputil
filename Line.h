//
// Created by Semyon Tikhonenko on 6/7/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_LINE_H
#define VOCALTRAINER_LINE_H

#include "Point.h"
#include "GeometryUtils.h"
#include "MathUtils.h"

namespace CppUtils {
    template <typename T>
    struct LineSegment;

    template<typename T>
    struct Line {
        Point<T> A;
        Point<T> B;

        explicit Line(const Point<T> &A, const Point<T> &B) : A(A), B(B) {
        }

        Line(T x1, T y1, T x2, T y2) : A(x1, y1), B(x2, y2) {

        }

        Line() = default;

        bool intersects(const Line<T>& other) const {
            return GeometryUtils::GetLinesIntersection(A.x, A.y, B.x, B.y, other.A.x,
                    other.A.y, other.B.x, other.B.y, nullptr, nullptr);
        }

        bool getIntersection(const Line<T>& other, Point<T>* outIntersection) const {
            return GeometryUtils::GetLinesIntersection(A.x, A.y, B.x, B.y, other.A.x,
                    other.A.y, other.B.x, other.B.y, &outIntersection->x, &outIntersection->y);
        }

        bool getIntersection(const LineSegment<T>& other, Point<T>* outIntersection) const {
            return other.getIntersection(*this, outIntersection);
        }

        bool intersects(const LineSegment<T>& other) const {
            return other.intersects(*this);
        }

        bool operator==(const Line<T> &rhs) const {
            return A == rhs.A &&
                    B == rhs.B;
        }

        bool operator!=(const Line<T> &rhs) const {
            return !(rhs == *this);
        }
    };

    template <typename T>
    struct LineSegment {
        Point<T> A;
        Point<T> B;

        explicit LineSegment(const Point <T> &A, const Point <T> &B) : A(A), B(B) {}
        LineSegment(T x1, T y1, T x2, T y2) : A(x1, y1), B(x2, y2) {}
        LineSegment() = default;

        bool getIntersection(const Line<T>& other, Point<T>* outIntersection) const {
            return asLine().getIntersection(other, outIntersection) &&
                           Math::IsInClosedInterval(A.x, B.x, outIntersection->x) &&
                    Math::IsInClosedInterval(A.y, B.y, outIntersection->y);
        }

        bool getIntersection(const LineSegment<T>& other, Point<T>* outIntersection) const {
            return asLine().getIntersection(other.asLine(), outIntersection) &&
                   Math::IsInClosedInterval(A.x, B.x, outIntersection->x) &&
                   Math::IsInClosedInterval(A.y, B.y, outIntersection->y) &&
                   Math::IsInClosedInterval(other.A.x, other.B.x, outIntersection->x) &&
                   Math::IsInClosedInterval(other.A.y, other.B.y, outIntersection->y);
        }

        bool intersects(const Line<T>& other) const {
            Point<T> _;
            return getIntersection(other, &_);
        }

        bool intersects(const LineSegment<T>& other) const {
            Point<T> _;
            return getIntersection(other, &_);
        }

        Line<T>& asLine() {
            return *reinterpret_cast<Line<T>*>(this);
        }

        const Line<T>& asLine() const {
            return *reinterpret_cast<const Line<T>*>(this);
        }
    };

    typedef Line<float> LineF;
    typedef Line<double> LineD;
    typedef LineSegment<float> LineSegmentF;
    typedef LineSegment<double> LineSegmentD;
}


#endif //VOCALTRAINER_LINE_H
