//
// Created by Semyon Tykhonenko on 8/25/19.
// Copyright (c) 2019 Semyon Tikhonenko. All rights reserved.
//

#ifndef VOCALTRAINER_ENUMMAP_H
#define VOCALTRAINER_ENUMMAP_H

#include <initializer_list>
#include <vector>
#include <iostream>

namespace CppUtils {
    // Supports only enums started from 0 and without gaps
    template <typename EnumType, typename RawValue>
    class EnumMap {
        std::vector<RawValue> values;
    public:
        EnumMap(std::initializer_list<RawValue> list) {
            values.resize(list.size());
            int index = 0;
            for (const RawValue& rawValue : list) {
                 values[index++] = rawValue;
            }
        }

        const RawValue& operator[](EnumType key) const {
            assert(size_t(key) < values.size());
            return values[size_t(key)];
        }
    };
}

#endif //VOCALTRAINER_ENUMMAP_H
