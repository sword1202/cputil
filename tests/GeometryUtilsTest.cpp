//
// Created by Semyon Tikhonenko on 2/3/17.
//

#ifndef CPP_UTILS_NO_CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"
#include "../GeometryUtils.h"
#include "../Algorithms.h"
#include "../RoundedRect.h"

constexpr float epsilon = 0.01;

using namespace CppUtils::GeometryUtils;
using namespace CppUtils;

//TEST_CASE("lines intersection test") {
//
//    //A
//    float line1x1 = 5;
//    float line1y1 = 3;
//
//    //B
//    float line1x2 = 10;
//    float line1y2 = 3;
//
//    //C
//    float line2x1 = 25;
//    float line2y1 = 0;
//
//    // D
//    float line2x2 = 25;
//    float line2y2 = -15;
//
//    float intersectionX, intersectionY;
//    bool intersects = GetLinesIntersection(line1x1, line1y1, line1x2, line1y2,
//                                           line2x1, line2y1, line2x2, line2y2, &intersectionX, &intersectionY);
//    REQUIRE(intersects);
//    REQUIRE(intersectionX == 25);
//    REQUIRE(intersectionY == 3);
//
//    //A
//    line1x1 = 5;
//    line1y1 = 3;
//
//    //B
//    line1x2 = 10;
//    line1y2 = 3;
//
//    //C
//    line2x1 = 15;
//    line2y1 = 5;
//
//    // D
//    line2x2 = 25;
//    line2y2 = 5;
//
//    intersectionX = 0, intersectionY = 0;
//    intersects = GetLinesIntersection(line1x1, line1y1, line1x2, line1y2,
//                                      line2x1, line2y1, line2x2, line2y2, &intersectionX, &intersectionY);
//    REQUIRE(!intersects);
//    REQUIRE(intersectionX == 0);
//    REQUIRE(intersectionY == 0);
//
//    LineF line1(5, -9, 5, 2);
//    LineF line2(2, -7, 8, -7);
//
//    PointF intersection;
//    REQUIRE(line1.getIntersection(line2, &intersection));
//
//    REQUIRE(intersection == PointF(5, -7));
//}

//TEST_CASE("circle-line intersections test") {
//    CircleF circle(PointF(4, 0), 2);
//    LineF line(0, 0, 8, 0);
//
//    PointF intersection1;
//    PointF intersection2;
//    REQUIRE(circle.getIntersections(line, &intersection1, &intersection2) == 2);
//
//    bool equals1 = intersection1 == PointF(2, 0) || intersection1 == PointF(6, 0);
//    bool equals2 = intersection2 == PointF(2, 0) || intersection2 == PointF(6, 0);
//    REQUIRE(equals1);
//    REQUIRE(equals2);
//
//    line = LineF(0, -2, 8, -2);
//
//    REQUIRE(circle.getIntersections(line, &intersection1, &intersection2) == 1);
//
//    REQUIRE(intersection1 == PointF(4, -2));
//
//    line = LineF(1, -3, 7, 3);
//
//    REQUIRE(circle.getIntersections(line, &intersection1, &intersection2) == 2);
//
//    PointF point1 = circle.getPointForAngle(M_PI * 2 - M_PI_4);
//    PointF point2 = circle.getPointForAngle(M_PI_2 + M_PI_4);
//    equals1 = intersection1.compareUsingEpsilon(point1, epsilon) || intersection1.compareUsingEpsilon(point2, epsilon);
//    equals2 = intersection2.compareUsingEpsilon(point1, epsilon) || intersection2.compareUsingEpsilon(point2, epsilon);
//    REQUIRE(equals1);
//    REQUIRE(equals2);
//
//    line = LineF(2, -4, 8, 2);
//
//    // add some epsilon
//    REQUIRE(circle.getIntersectionsForArc(line, -epsilon + M_PI_2 * 3, M_PI * 2 + epsilon, &intersection1, &intersection2) == 2);
//
//    point1 = PointF(6, 0);
//    point2 = PointF(4, -2);
//    equals1 = intersection1.compareUsingEpsilon(point1, epsilon) || intersection1.compareUsingEpsilon(point2, epsilon);
//    equals2 = intersection2.compareUsingEpsilon(point1, epsilon) || intersection2.compareUsingEpsilon(point2, epsilon);
//    REQUIRE(equals1);
//    REQUIRE(equals2);
//
//    REQUIRE(circle.getIntersectionsForArc(line, -epsilon, M_PI_4 + epsilon, &intersection1, &intersection2) == 1);
//}

TEST_CASE("roundrect-line intersections test") {
    RoundedRectF rect(PointF(0, -7), 10, 7, 2);

    LineF line(5, 2, 5, -9);

    PointF intersection1;
    PointF intersection2;
    //REQUIRE(rect.getIntersectionsWithLine(line, &intersection1, &intersection2) == 2);

    bool equals1 = intersection1 == PointF(5, 0) || intersection1 == PointF(5, -7);
    bool equals2 = intersection2 == PointF(5, 0) || intersection2 == PointF(5, -7);
//    REQUIRE(equals1);
//    REQUIRE(equals2);

    line = LineF(6, 2, 12, -4);
    REQUIRE(rect.getIntersectionsWithLine(line, &intersection1, &intersection2) == 2);

    equals1 = intersection1 == PointF(8, 0) || intersection1 == PointF(10, -2);
    equals2 = intersection2 == PointF(8, 0) || intersection2 == PointF(10, -2);
    REQUIRE(equals1);
    REQUIRE(equals2);
}
