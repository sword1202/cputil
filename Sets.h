//
// Created by Semyon Tikhonenko on 7/21/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_SETS_H
#define VOCALTRAINER_SETS_H

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
    }
};


#endif //VOCALTRAINER_SETS_H
