//
// Created by Semyon Tikhonenko on 6/7/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_CIRCLE_H
#define VOCALTRAINER_CIRCLE_H

#include "Point.h"
#include "Line.h"
#import "MathUtils.h"
#include <assert.h>
#include <array>

namespace CppUtils {

    template <typename Float>
    class Circle {
        Float radius = 1;
    public:
        Point<Float> center;

        Circle(const Point<Float> &center, Float radius) : radius(radius), center(center) {
        }

        Circle() {
        }

        Float getRadius() const {
            return radius;
        }

        void setRadius(Float radius) {
            assert(radius >= 0);
            this->radius = radius;
        }

        int getIntersections(const Line<Float> &line, Point<Float>* outPoint1, Point<Float>* outPoint2) {
            Float dx, dy, A, B, C, det, t;

            Float x2 = line.B.x;
            Float x1 = line.A.x;
            Float y2 = line.B.y;
            Float y1 = line.A.y;

            dx = x2 - x1;
            dy = y2 - y1;

            A = dx * dx + dy * dy;
            B = 2 * (dx * (x1 - center.x) + dy * (y1 - center.y));
            C = (x1 - center.x) * (x1 - center.x) +
                    (y1 - center.y) * (y1 - center.y) -
                    radius * radius;

            det = B * B - 4 * A * C;
            if ((A <= 0.0000001) || (det < 0)) {
                return 0;
            } else if (det == 0) {
                // One solution.
                t = -B / (2 * A);
                *outPoint1 = Point<Float>(x1 + t * dx, y1 + t * dy);
                return 1;
            } else {
                // Two solutions.
                t = (float)((-B + sqrt(det)) / (2 * A));
                *outPoint1 = Point<Float>(x1 + t * dx, y1 + t * dy);
                t = (float)((-B - sqrt(det)) / (2 * A));
                *outPoint2 = Point<Float>(x1 + t * dx, y1 + t * dy);
                return 2;
            }
        }

        int getIntersections(const Line<Float> &line, std::array<Point<Float>, 2> *outPoints) {
            return getIntersections(line, &(*outPoints)[0], &(*outPoints)[1]);
        }

        int getIntersectionsForArc(
                const Line<Float> &line,
                Float angleBegin,
                Float angleEnd,
                std::array<Point<Float>, 2> *outPoints)
        {
            std::array<Point<Float>, 2> temp;
            int tempCount = getIntersections(line, &temp);
            int resultCount = 0;
            for (int i = 0; i < tempCount; ++i) {
                float angle = acos((temp[i].x - center.x) / radius);
                if (Math::isAngleBetweenAngles(angle, angleBegin, angleEnd)) {
                    (*outPoints)[i] = temp[i];
                    resultCount++;
                }
            }

            return resultCount;
        }

        int getIntersectionsForArc(
                const Line<Float> &line,
                Float angleBegin,
                Float angleEnd,
                Point<Float>* outPoint1,
                Point<Float>* outPoint2)
        {
            std::array<Point<Float>, 2> points;
            int count = getIntersectionsForArc(line, angleBegin, angleEnd, &points);
            if (count >= 1) {
                *outPoint1 = points[0];

                if (count >= 2) {
                    *outPoint2 = points[1];
                }
            }

            return count;
        }

        /*
         * 0 --------x-------- >
         * |
         * |
         * | Coordinate system
         * y
         * |
         * \/
         */
        Point<Float> getPointForAngle(Float angle) {
            return Point<Float>(center.x + radius * cos(angle), -center.y - radius * sin(angle));
        }

        bool operator==(const Circle &rhs) const {
            return radius == rhs.radius &&
                    center == rhs.center;
        }

        bool operator!=(const Circle &rhs) const {
            return !(rhs == *this);
        }
    };

    typedef Circle<float> CircleF;
    typedef Circle<double> CircleD;
}


#endif //VOCALTRAINER_CIRCLE_H
