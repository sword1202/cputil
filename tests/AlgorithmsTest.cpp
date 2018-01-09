#include "catch.hpp"
#include "../Algorithms.h"

using namespace CppUtils;

TEST_CASE("FindLessOrEqualInSortedCollection") {
    std::vector<int> a = {1,2,3,4,5,6,9,10};
    REQUIRE(*CppUtils::FindLessOrEqualInSortedCollection(a, 6) == 6);
    REQUIRE(*CppUtils::FindLessOrEqualInSortedCollection(a, 7) == 6);
    REQUIRE(CppUtils::FindLessOrEqualInSortedCollection(a, 0) == a.end());
}