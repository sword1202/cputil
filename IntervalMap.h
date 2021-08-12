//
// Created by Semyon Tikhonenko on 8/12/21.
// Copyright (c) 2021 Semyon Tikhonenko. All rights reserved.
//

#ifndef VOCALTRAINER_INTERVALMAP_H
#define VOCALTRAINER_INTERVALMAP_H

#include <boost/icl/interval_map.hpp>
#include <set>
#include "Sets.h"

namespace CppUtils {
    // Simplified wrapper for boost::icl::interval_map usable in most cases. Use boost::icl directly for more advanced behaviour
    template <typename Key, typename Value>
    class IntervalMap {
        boost::icl::interval_map<Key, std::set<Value>> map;
    public:
        // [start, end)
        void add(const Key& start, const Key& end, const Value& value) {
            map += std::make_pair(boost::icl::interval<Key>::right_open(start, end), std::set<Value> {value});
        }

        const std::set<Value>& get(const Key& point) const {
            auto iter = map.find(point);
            if (iter == map.end()) {
                return Sets::emptySet<Value>();
            }

            return iter->second;
        }

        void clear() {
            map.clear();
        }

        bool empty() const {
            return map.empty();
        }
    };
}

#endif //VOCALTRAINER_INTERVALMAP_H
