//
// Created by Semyon Tikhonenko on 6/8/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_ROUNDEDRECT_H
#define VOCALTRAINER_ROUNDEDRECT_H

#import <cassert>
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include <array>

namespace CppUtils {

    template <typename Float>
    class RoundedRect {
        Float radius;
    public:
        Point<Float> A;
        Float width;
        Float height;

        RoundedRect(const Point<Float> &A, Float width, Float height, Float radius)
                : radius(radius), A(A), width(width), height(height) {
        }

        Float getRadius() const {
            return radius;
        }

        void setRadius(Float radius) {
            assert(radius >= 0);
            this->radius = radius;
        }

        int getIntersectionsWithLine(const Line<Float>& line, Point<Float>* outPoint1, Point<Float>* outPoint2) {
            assert(outPoint1 && outPoint2);
            std::array<Point<Float>, 2> intersections;
            int count = getIntersectionsWithLine(line, &intersections);
            if (count >= 1) {
                *outPoint1 = intersections[0];

                if (count >= 2) {
                    *outPoint2 = intersections[1];
                }
            }

            return count;
        }

        int getIntersectionsWithLine(const Line<Float>& line, std::array<Point<Float>, 2>* intersections) {
            int intersectionsCount = 0;
            std::array<LineSegment<Float>, 4> sides;
            sides[0] = LineSegment<Float>(A.x + radius, A.y, A.x + width - radius, A.y);
            sides[1] = LineSegment<Float>(A.x + radius, A.y + height, A.x + width - radius, A.y + height);
            sides[2] = LineSegment<Float>(A.x, A.y + radius, A.x, A.y + height - radius);
            sides[3] = LineSegment<Float>(A.x + width, A.y + radius, A.x + width, A.y + height - radius);

            Point<Float> intersection;
            for (int i = 0; i < sides.size(); ++i) {
                if (line.getIntersection(sides[i], &intersection)) {
                    (*intersections)[intersectionsCount++] = intersection;

                    if (intersectionsCount >= 2) {
                        return intersectionsCount;
                    }
                }
            }

            std::array<Point<Float>, 4> centers;
            centers[0] = Point<Float>(A.x + radius, A.y + radius);
            centers[1] = Point<Float>(A.x + width - radius, A.y + radius);
            centers[2] = Point<Float>(A.x + radius, A.y + height - radius);
            centers[3] = Point<Float>(A.x + width - radius, A.y + height - radius);

            Float angles[4][2] = {{M_PI_2, M_PI}, {0, M_PI_2},
                                  {M_PI, M_PI + M_PI_2}, {M_PI_2 + M_PI, 2 * M_PI}};

            for (int i = 0; i < centers.size(); ++i) {
                Circle<Float> circle(centers[i], radius);
                std::array<Point<Float>, 2> outPoints;
                int tempIntersectionsCount = circle.getIntersectionsForArc(line, angles[i][0], angles[i][1], &outPoints);
                assert(tempIntersectionsCount < 3);

                for (int j = 0; j < tempIntersectionsCount; ++j) {
                    (*intersections)[intersectionsCount++] = outPoints[j];
                    if (intersectionsCount >= 2) {
                        return intersectionsCount;
                    }
                }

                if (intersectionsCount >= 2) {
                    return intersectionsCount;
                }
            }

            return intersectionsCount;
        }

        bool operator==(const RoundedRect &rhs) const {
            return radius == rhs.radius &&
                   A == rhs.A &&
                   width == rhs.width &&
                   height == rhs.height;
        }

        bool operator!=(const RoundedRect &rhs) const {
            return !(rhs == *this);
        }
    };

    typedef RoundedRect<float> RoundedRectF;
    typedef RoundedRect<double> RoundedRectD;
}


#endif //VOCALTRAINER_ROUNDEDRECT_H
