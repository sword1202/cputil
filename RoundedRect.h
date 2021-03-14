//
// Created by Semyon Tikhonenko on 6/8/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_ROUNDEDRECT_H
#define VOCALTRAINER_ROUNDEDRECT_H

#include <assert.h>

#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "Rect.h"
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
            assert(width >= radius * 2);
            assert(height >= radius * 2);
        }

        RoundedRect(Float x, Float y, Float width, Float height, Float radius)
                : RoundedRect(Point<Float>(x, y), width, height, radius) {}

        Float getRadius() const {
            return radius;
        }

        void setRadius(Float radius) {
            assert(radius >= 0);
            this->radius = radius;
        }

        void validate() {
            assert(width >= 0);
            assert(height >= 0);

            if (width < radius * 2) {
                radius = width / 2;
            }

            if (height < radius * 2) {
                radius = height / 2;
            }
        }

        int getIntersectionsWithLineSegment(const LineSegment<Float>& segment,
                                            Point<Float>* outPoint1,
                                            Point<Float>* outPoint2) const {
            std::array<Point<Float>, 2> intersections;
            int count = getIntersectionsWithLineSegment(segment, &intersections);
            *outPoint1 = intersections[0];
            *outPoint2 = intersections[1];

            return count;
        }

        int getIntersectionsWithLineSegment(const LineSegment<Float>& segment, std::vector<Point<Float>>* outIntersections) const {
            std::array<Point<Float>, 2> intersections;
            int count = getIntersectionsWithLineSegment(segment, &intersections);
            std::copy(intersections.begin(), intersections.begin() + count, std::back_inserter(*outIntersections));
            return count;
        }

        int getIntersectionsWithLineSegment(const LineSegment<Float>& segment,
                                            std::array<Point<Float>, 2>* outIntersections) const {
            std::array<Point<Float>, 2>& intersections = *outIntersections;
            int count = getIntersectionsWithLine(segment.asLine(), outIntersections);
            if (count == 1) {
                if (segment.containsPoint(intersections[0])) {
                    return 1;
                }

                return 0;
            }

            if (count == 0) {
                return 0;
            }

            if (count == 2) {
                bool contains[] = {
                        segment.containsPoint(intersections[0]),
                        segment.containsPoint(intersections[1])
                };

                if (!contains[0] && !contains[1]) {
                    return 0;
                } else if(contains[0] && contains[1]) {
                    return 2;
                }

                if (contains[0]) {
                    intersections[1] = LineSegment<Float>(intersections[0], intersections[1]).containsPoint(segment.A)
                                       ? segment.A : segment.B;
                } else if(contains[1]) {
                    intersections[0] = LineSegment<Float>(intersections[0], intersections[1]).containsPoint(segment.A)
                                       ? segment.A : segment.B;
                }

                return 2;
            }

            return 0;
        }

        int getIntersectionsWithLine(const Line<Float>& line, Point<Float>* outPoint1, Point<Float>* outPoint2) const {
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

        LineSegment<Float> getTopSide() const {
            return LineSegment<Float>(A.x + radius, A.y, A.x + width - radius, A.y);
        }

        LineSegment<Float> getBottomSide() const {
            return LineSegment<Float>(A.x + radius, A.y + height, A.x + width - radius, A.y + height);
        }

        LineSegment<Float> getLeftSide() const {
            return LineSegment<Float>(A.x, A.y + radius, A.x, A.y + height - radius);
        }

        LineSegment<Float> getRightSide() const {
            return LineSegment<Float>(A.x + width, A.y + radius, A.x + width, A.y + height - radius);
        }

        int getIntersectionsWithLine(const Line<Float>& line, std::array<Point<Float>, 2>* intersections) const {
            int intersectionsCount = 0;
            std::array<LineSegment<Float>, 4> sides = {getTopSide(), getBottomSide(), getLeftSide(), getRightSide()};

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

        bool containsPoint(Float x, Float y) const {
            return Rect<Float>(A.x + radius, A.y, width - radius * 2, height).containsPoint(x, y)
                    || Rect<Float>(A.x, A.y + radius, width, height - radius * 2).containsPoint(x, y)
                    || Circle<Float>(Point<Float>(A.x + radius, A.y + radius), radius).containsPoint(x, y)
                    || Circle<Float>(Point<Float>(A.x + width - radius, A.y + radius), radius).containsPoint(x, y)
                    || Circle<Float>(Point<Float>(A.x + radius, A.y + height - radius), radius).containsPoint(x, y)
                    || Circle<Float>(Point<Float>(A.x + width - radius, A.y + height - radius), radius).containsPoint(x, y);
        }

        bool containsPoint(const Point<Float>& point) const {
            return containsPoint(point.x, point.y);
        }

        bool operator==(const RoundedRect<Float> &rhs) const {
            return radius == rhs.radius &&
                   A == rhs.A &&
                   width == rhs.width &&
                   height == rhs.height;
        }

        bool operator!=(const RoundedRect<Float> &rhs) const {
            return !(rhs == *this);
        }

        void translate(Float x, Float y) {
            A.translate(x, y);
        }

        Rect<Float> toRect() const {
            return Rect<Float>(A, width, height);
        }

        friend std::ostream &operator<<(std::ostream &os, const RoundedRect &rect) {
            os << rect.A << " width: " << rect.width << " height: " << rect.height << " radius: " << rect.radius;
            return os;
        }
    };

    typedef RoundedRect<float> RoundedRectF;
    typedef RoundedRect<double> RoundedRectD;
}


#endif //VOCALTRAINER_ROUNDEDRECT_H
