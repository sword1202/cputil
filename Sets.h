//
// Created by Semyon Tikhonenko on 7/21/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_SETS_H
#define VOCALTRAINER_SETS_H

#include <algorithm>
#include <set>

namespace CppUtils {
    namespace Sets {
        template <typename Set1, typename Set2, typename Result = Set1>
        Result Difference(const Set1& a, const Set2& b) {
            Result result;
            std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.end()));
            return result;
        }

        template <typename Set1, typename Set2, typename OutContainer>
        void Difference(const Set1& a, const Set2& b, OutContainer* result) {
            std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(*result, result->end()));
        }

        template <typename Set1, typename Set2, typename OutIterator>
        void Difference(const Set1& a, const Set2& b, OutIterator outIterator) {
            std::set_difference(a.begin(), a.end(), b.begin(), b.end(), outIterator);
        }

        template <typename Set>
        auto FindOrDefault(const Set& set, decltype(*set.begin()) value, decltype(*set.begin()) defaultValue) {
            auto iter = set.find(value);
            if (iter == set.end()) {
                return defaultValue;
            }

            return *iter;
        }

        template <typename Set, typename Function>
        void Filter(Set& set, const Function& function) {
            for (auto iter = set.begin(); iter != set.end();) {
                if (function(*iter)) {
                    ++iter;
                } else {
                    set.erase(iter++);
                }
            }
        }

        template <typename T>
        const std::set<T>& emptySet() {
            static std::set<T> s;
            return s;
        }
    }
};


#endif //VOCALTRAINER_SETS_H
