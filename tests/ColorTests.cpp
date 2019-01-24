//
// Created by Semyon Tikhonenko on 2019-01-24.
//

#include "catch.hpp"
#include "Color.h"

using namespace CppUtils;

TEST_CASE("ColorTests fromHexString") {
    REQUIRE(Color::fromHexString("ffffff") == Color::white());
    REQUIRE(Color::fromHexString("ff000000") == Color::black());
    REQUIRE(Color::fromHexString("00000000") == Color::transparent());
    REQUIRE(Color::fromHexString("ddeecc00") == Color(0xee, 0xcc, 0x00, 0xdd));
}

TEST_CASE("ColorTests toHexString") {
    REQUIRE(Color(0xee, 0xcc, 0x00, 0xdd).toHexString() == "ddeecc00");
    REQUIRE(Color::white().toHexString() == "ffffffff");
    REQUIRE(Color::transparent().toHexString() == "00000000");
    REQUIRE(Color::black().toHexString() == "ff000000");
    REQUIRE(Color::fromHexString("ddeecc00").toHexString() == "ddeecc00");
}

