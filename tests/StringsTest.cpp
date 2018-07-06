
#include "../StringUtils.h"
#include "catch.hpp"

using namespace CppUtils::Strings;

TEST_CASE("join") {
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
}

TEST_CASE("replace") {
    std::string str = "abcefd";
    REQUIRE(ReplaceFirst(str, "abc", "34") == "34efd");
    str = "";
    REQUIRE(ReplaceFirst(str, "abc", "34") == "");
    str = "a3";
    REQUIRE(ReplaceFirst(str, "abc", "34") == "a3");

    str = "abcefd";
    REQUIRE(ReplaceAll(str, "abc", "34") == "34efd");
    str = "aaaaaa";
    REQUIRE(ReplaceAll(str, "a", "b") == "bbbbbb");
    str = "aaaaaa";
    REQUIRE(ReplaceAll(str, "c", "b") == "aaaaaa");
    str = "aaaaaa";
    REQUIRE(ReplaceAll(str, "", "b") == "aaaaaa");
    str = "aaaaaa";
    REQUIRE(ReplaceAll(str, "a", "") == "");
}

TEST_CASE("starts with") {
    std::string str = "12345";
    REQUIRE(StartsWith(str, "123"));
    REQUIRE(StartsWith(str, ""));
    REQUIRE_FALSE(StartsWith(str, "34"));
    REQUIRE(StartsWith(str, std::string("123")));
    REQUIRE(StartsWith(str, std::string("")));
    REQUIRE_FALSE(StartsWith(str, std::string("34")));
}

TEST_CASE("stream to string") {
    std::istringstream stream("abcd");
    REQUIRE(StreamToString(stream) == "abcd");
}

TEST_CASE("split") {
    REQUIRE(Split("", ',') == std::vector<std::string>());
    REQUIRE(Split("werterw,343443,sdfgdfsg,", ',') == std::vector<std::string> {"werterw", "343443", "sdfgdfsg", ""});
    REQUIRE(Split("werterw,343443,sdfgdfsg", ',') == std::vector<std::string> {"werterw", "343443", "sdfgdfsg"});
    REQUIRE(Split("werterw", ',') == std::vector<std::string> {"werterw"});
    REQUIRE(Split("werterw,343443,sdfgdfsg,", 5, 10, ',') == std::vector<std::string> {"rw","34"});
    bool success;
    REQUIRE(SplitIntegers("12,345,4567", 0, 10, ',', &success) == std::vector<int> {12, 345, 456});
    REQUIRE(success);

    SplitIntegers("12,dsds,3", 0, 10, ',', &success);
    REQUIRE(!success);
}