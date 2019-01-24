//
// Created by Semyon Tikhonenko on 2019-01-22.
//

#ifndef TEXTIMAGESGENERATOR_BINARYMATH_H
#define TEXTIMAGESGENERATOR_BINARYMATH_H

#include <assert.h>

namespace CppUtils {
    namespace BinaryMath {
        template<typename Integer>
        unsigned char GetByte(Integer integer, int index) {
            assert(index < sizeof(integer));
            return (integer >> (index * 8));
        }
    };
}


#endif //TEXTIMAGESGENERATOR_BINARYMATH_H
