//
// Created by Semyon Tikhonenko on 2018-12-19.
//


#include "catch.hpp"
#include "../PointerOrObject.h"

TEST_CASE("test 1") {
    PointerOrObject<std::string> o;
    *o = "abc";
    REQUIRE(*o == "abc");
    std::string str = "yoyoyo";
    o = &str;
    REQUIRE(*o == "yoyoyo");
    str[0] = 'a';
    REQUIRE(*o == "aoyoyo");
}

TEST_CASE("test 2") {
    PointerOrObject<std::string> o;
    o = "abc";
    REQUIRE(*o == "abc");
    std::string str = "yoyoyo";
    o = &str;
    REQUIRE(*o == "yoyoyo");
    str[0] = 'a';
    REQUIRE(*o == "aoyoyo");
    *o = "ebi gusey";
    REQUIRE(str == "ebi gusey");
}

static void changeStr(std::string& str) {
    str = "lalala";
}

TEST_CASE("test 2") {
    PointerOrObject<std::string> o;
    changeStr(*o);
    REQUIRE(*o == "lalala");
}
