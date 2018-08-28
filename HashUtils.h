//
// Created by Semyon Tikhonenko on 6/8/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_HASHUTILS_H
#define VOCALTRAINER_HASHUTILS_H

#include <unordered_set>

#define MAKE_HASHABLE(type, ...) \
    namespace std {\
        template<> struct hash<type> {\
            std::size_t operator()(const type &t) const {\
                std::size_t ret = 0;\
                CppUtils::HashCombine(ret, __VA_ARGS__);\
                return ret;\
            }\
        };\
    }

#define MAKE_HASHABLE_TEMPLATE1(type, ...) \
    namespace std {\
        template<typename T1> struct hash<type<T1>> {\
            std::size_t operator()(const type<T1> &t) const {\
                std::size_t ret = 0;\
                CppUtils::HashCombine(ret, __VA_ARGS__);\
                return ret;\
            }\
        };\
    }

namespace CppUtils {
    inline void HashCombine(std::size_t& seed) {}

    template<typename T, typename... Rest>
    inline void HashCombine(std::size_t &seed, const T &v, Rest... rest) {
        std::hash <T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        HashCombine(seed, rest...);
    }
}


#endif //VOCALTRAINER_HASHUTILS_H
