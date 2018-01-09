//
// Created by Semyon Tikhonenko on 8/7/16.
//

#ifndef PITCHDETECTION_AZAZAI_ALGO_H
#define PITCHDETECTION_AZAZAI_ALGO_H

#include <algorithm>

namespace CppUtils {
    template<typename Iterator, typename Element>
    Iterator FindNearestElementInSortedCollection(Iterator begin, Iterator end, const Element &value) {
        if (begin == end) {
            return end;
        }

        Iterator lowerBound = std::lower_bound(begin, end, value);

        if (lowerBound == end) {
            return lowerBound - 1;
        }

        if (*lowerBound == value) {
            return lowerBound;
        }

        Element downDistance = value - *(lowerBound - 1);
        Element upDistance = *lowerBound - value;

        if (upDistance > downDistance) {
            return lowerBound - 1;
        } else {
            return lowerBound;
        }
    };

    template<typename Collection, typename Value, typename Predicate>
    typename Collection::iterator FindLessOrEqualInSortedCollection(Collection& collection,
            const Value& value, const Predicate& predicate) {
        auto upper = std::upper_bound(collection.begin(), collection.end(), value, predicate);
        if (upper == collection.begin()) {
            return collection.end();
        }

        return upper - 1;
    }

    template<typename Collection, typename Value>
    typename Collection::iterator FindLessOrEqualInSortedCollection(Collection& collection,
                                                                    const Value& value) {
        return FindLessOrEqualInSortedCollection(collection, value, [&] (const Value& a, const Value& b) {
            return a < b;
        });

    }
};

#endif //PITCHDETECTION_AZAZAI_ALGO_H
