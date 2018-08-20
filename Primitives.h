#ifndef CPP_UTILS_PRIMITIVES_H
#define CPP_UTILS_PRIMITIVES_H

#include <limits>
#include <cmath>


namespace CppUtils {
namespace Primitives {
    template<typename Float>
    bool CompareFloats(Float a, Float b) {
        Float epsilon = std::numeric_limits<Float>::epsilon();
        return fabs(a - b) < epsilon;
    }

    template<typename Float>
    bool CompareFloatsUsingEpsilon(Float a, Float b, Float epsilon) {
        return fabs(a - b) < epsilon;
    }
}
}

#endif
