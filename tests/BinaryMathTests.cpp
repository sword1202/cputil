//
// Created by Semyon Tikhonenko on 2019-01-22.
//

#include "catch.hpp"
#include "BinaryMath.h"

using namespace CppUtils::BinaryMath;

TEST_CASE("getByte") {
    int value = 0xffaaccdd;
    REQUIRE(GetByte(value, 0) == 0xdd);
    REQUIRE(GetByte(value, 1) == 0xcc);
    REQUIRE(GetByte(value, 2) == 0xaa);
    REQUIRE(GetByte(value, 3) == 0xff);
}

