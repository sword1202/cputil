//
// Created by Semyon Tikhonenko on 10/2/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_MAPS_H
#define VOCALTRAINER_MAPS_H

#include <vector>
#include <algorithm>

namespace CppUtils {
    namespace Maps {
        template<typename Map, typename Value>
        void Values(const Map& map, std::vector<Value>* result) {
            result->resize(map.size());
            std::transform(map.begin(), map.end(), result->begin(), [] (const auto& pair) {
                return pair.second;
            });
        }

        template<typename Map>
        auto Values(const Map& map) {
            std::vector<decltype(map.begin()->second)> result;
            Values(map, &result);
            return result;
        }

        template <typename K, typename V>
        const std::map<K, V>& emptyMap() {
            static std::map<K, V> map;
            return map;
        }
    };
}

#endif //VOCALTRAINER_MAPS_H
