//
// Created by Semyon Tikhonenko on 2/3/17.
//

#ifndef CPP_UTILS_NO_CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"
#include "../GeometryUtils.h"

using namespace CppUtils::GeometryUtils;

TEST_CASE("lines intersection test") {

    //A
    float line1x1 = 5;
    float line1y1 = 3;

    //B
    float line1x2 = 10;
    float line1y2 = 3;

    //C
    float line2x1 = 25;
    float line2y1 = 0;

    // D
    float line2x2 = 25;
    float line2y2 = -15;

    float intersectionX, intersectionY;
    bool intersects = GetLinesIntersection(line1x1, line1y1, line1x2, line1y2,
                                           line2x1, line2y1, line2x2, line2y2, &intersectionX, &intersectionY);
    REQUIRE(intersects);
    REQUIRE(intersectionX == 25);
    REQUIRE(intersectionY == 3);

    //A
    line1x1 = 5;
    line1y1 = 3;

    //B
    line1x2 = 10;
    line1y2 = 3;

    //C
    line2x1 = 15;
    line2y1 = 5;

    // D
    line2x2 = 25;
    line2y2 = 5;

    intersectionX = 0, intersectionY = 0;
    intersects = GetLinesIntersection(line1x1, line1y1, line1x2, line1y2,
                                      line2x1, line2y1, line2x2, line2y2, &intersectionX, &intersectionY);
    REQUIRE(!intersects);
    REQUIRE(intersectionX == 0);
    REQUIRE(intersectionY == 0);
}
