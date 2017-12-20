
#include "../Strings.h"
#include "catch.hpp"

using namespace CppUtils::Strings;

TEST_CASE("join test") {
    std::vector<int> a = {1,2,3,4,55,29};
    REQUIRE(Join(a.begin(), a.end(), ",") == "1,2,3,4,55,29");
    REQUIRE(Join(a, ",") == "1,2,3,4,55,29");
    a = {};
    REQUIRE(Join(a.begin(), a.end(), ",").empty());
    REQUIRE(Join(a, ",").empty());
    a = {124};
    REQUIRE(Join(a.begin(), a.end(), ",") == "124");
    REQUIRE(Join(a, ",") == "124");

    std::vector<std::string> e = {"a","abc","345","u","yyy","ddd"};
    REQUIRE(Join(e.begin(), e.end(), ", ") == "a, abc, 345, u, yyy, ddd");
    REQUIRE(Join(e, ", ") == "a, abc, 345, u, yyy, ddd");
    e = {};
    REQUIRE(Join(e.begin(), e.end(), ", ").empty());
    REQUIRE(Join(e, ", ").empty());
    e = {"sdsd"};
    REQUIRE(Join(e.begin(), e.end(), ", ") == "sdsd");
    REQUIRE(Join(e, ", ") == "sdsd");

    std::string str = "abcefd";
    REQUIRE(ReplaceFirst(str, std::string("abc"), std::string("34")) == "34efd");
}
