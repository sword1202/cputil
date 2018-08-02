#ifndef CPP_UTILS_PRIMITIVES_H
#define CPP_UTILS_PRIMITIVES_H

#ifdef _WIN32
 #include <limits>
 #include <cmath>
#else
 #import <limits>
 #import <cmath>
#endif



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
