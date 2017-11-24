//
// Created by Semyon Tikhonenko on 2/3/17.
//

#ifndef PITCHDETECTION_GEOMETRYUTILS_H
#define PITCHDETECTION_GEOMETRYUTILS_H


#include <cmath>
#include <limits>

namespace CppUtils {
    namespace GeometryUtils {
        template<typename Float> 
        bool getLinesIntersection(Float line1x1, Float line1y1, Float line1x2, Float line1y2,
                                  Float line2x1, Float line2y1, Float line2x2, Float line2y2,
                                  Float *intersectionX, Float *intersectionY) {
            Float s1_x, s1_y, s2_x, s2_y;
            s1_x = line1x2 - line1x1;     s1_y = line1y2 - line1y1;
            s2_x = line2x2 - line2x1;     s2_y = line2y2 - line2y1;

            Float t = ( s2_x * (line1y1 - line2y1) - s2_y * (line1x1 - line2x1)) / (-s2_x * s1_y + s1_x * s2_y);

            Float x = line1x1 + (t * s1_x);
            if (x != x) {
                return false;
            }

            Float y = line1y1 + (t * s1_y);
            if (y != y) {
                return false;
            }

            // Collision detected
            if (intersectionX) {
                *intersectionX = x;
            }
            if (intersectionY) {
                *intersectionY = y;
            }

            return true;
        }
    }
}


#endif //PITCHDETECTION_GEOMETRYUTILS_H
