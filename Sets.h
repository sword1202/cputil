//
// Created by Semyon Tikhonenko on 7/21/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_SETS_H
#define VOCALTRAINER_SETS_H

#include <algorithm>

namespace CppUtils {
    namespace Sets {
        template <typename Set>
        Set Difference(const Set& a, const Set& b) {
            Set result;
            std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.end()));
            return result;
        }

        template <typename Set, typename OutContainer>
        void Difference(const Set& a, const Set& b, OutContainer* result) {
            std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(*result, result->end()));
        }

        template <typename Set, typename OutIterator>
        void Difference(const Set& a, const Set& b, OutIterator outIterator) {
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
    }
};


#endif //VOCALTRAINER_SETS_H
