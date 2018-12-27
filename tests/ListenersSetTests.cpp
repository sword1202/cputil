//
// Created by Semyon Tikhonenko on 2018-12-27.
//

#include "../ListenersSet.h"
#include "../Primitives.h"
#include "catch.hpp"
#include <string>

using namespace CppUtils;

TEST_CASE("listener executed") {
    CppUtils::ListenersSet<double, int, const std::string&> listenersSet;
    bool executed;
    listenersSet.addListener([&] (double a, int b, const std::string& c) {
        REQUIRE(b == 5);
        REQUIRE(Primitives::CompareFloats(a, 123.45));
        REQUIRE(c == "yoyoyo");
        executed = true;
    });

    listenersSet.executeAll(123.45, 5, "yoyoyo");
    REQUIRE(executed);
}

namespace {
    struct FuncObj1 {
        bool executed = false;
        void operator()(const std::string& arg) {
            REQUIRE(arg == "arg");
            executed = true;
        }
    };
}

TEST_CASE("function pointer listener executed") {
    CppUtils::ListenersSet<const std::string&> listenersSet;
    FuncObj1 obj;
    listenersSet.addListener(&obj);
    listenersSet.executeAll("arg");
    REQUIRE(obj.executed);
}

TEST_CASE("execution order preserved test") {
    std::string result;
    CppUtils::ListenersSet<> listenersSet;
    listenersSet.addListener([&] {
        result.push_back('a');
    });
    listenersSet.addListener([&] {
        result.push_back('b');
    });
    auto c = [&] {
        result.push_back('c');
    };
    listenersSet.addListener(&c);
    listenersSet.addListener([&] {
        result.push_back('d');
    });
    auto e = [&] {
        result.push_back('e');
    };
    listenersSet.addListener(&e);
    listenersSet.executeAll();
    REQUIRE(result == "abcde");
}

TEST_CASE("execution order with removals preserved test") {
    std::string result;
    CppUtils::ListenersSet<> listenersSet;
    listenersSet.addListener([&] {
        result.push_back('a');
    });
    int b = listenersSet.addListener([&] {
        result.push_back('b');
    });
    auto c = [&] {
        result.push_back('c');
    };
    listenersSet.addListener(&c);
    listenersSet.addListener([&] {
        result.push_back('d');
    });
    auto e = [&] {
        result.push_back('e');
    };
    listenersSet.addListener(&e);
    auto f = [&] {
        result.push_back('f');
    };
    listenersSet.addListener(&f);

    listenersSet.executeAll();
    REQUIRE(result == "abcdef");
    result.clear();
    listenersSet.removeListener(&c);
    listenersSet.executeAll();
    REQUIRE(result == "abdef");
    result.clear();
    listenersSet.removeListener(&f);
    listenersSet.executeAll();
    REQUIRE(result == "abde");
    result.clear();
    listenersSet.removeListener(b);
    listenersSet.executeAll();
    REQUIRE(result == "ade");
}
