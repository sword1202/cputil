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

    template<typename Iterator, typename KeyProvider>
    void SortByKey(Iterator begin, Iterator end, const KeyProvider& keyProvider) {
        std::sort(begin, end, [&keyProvider](const decltype(*begin)& a, const decltype(*begin)& b) {
            return keyProvider(a) < keyProvider(b);
        });
    }

    template<typename Collection, typename KeyProvider>
    void SortByKey(Collection& collection, const KeyProvider& keyProvider) {
        SortByKey(collection.begin(), collection.end(), keyProvider);
    };

    // Returns an iterator pointing to the first element in the range [first, last) that is not
    // less than (i.e. greater or equal to) value, or last if no such element is found.
    template<typename Iterator, typename KeyProvider, typename Value>
    Iterator LowerBoundByKey(Iterator begin, Iterator end, const Value& value, const KeyProvider& keyProvider) {
        return std::lower_bound(begin, end, value, [&](const Value& a, const Value b){
            return keyProvider(a) < keyProvider(b);
        });
    }

    template<typename Collection, typename KeyProvider, typename Value>
    auto LowerBoundByKey(Collection& collection, const Value& value, const KeyProvider& keyProvider) {
        return LowerBoundByKey(collection.begin(), collection.end(), value, keyProvider);
    };

    // Returns an iterator pointing to the first element in the range [first, last)
    // that is greater than value, or last if no such element is found.
    template<typename Iterator, typename KeyProvider, typename Value>
    Iterator UpperBoundByKey(Iterator begin, Iterator end, const Value& value, const KeyProvider& keyProvider) {
        return std::upper_bound(begin, end, value, [&](const Value& a, const Value b){
            return keyProvider(a) < keyProvider(b);
        });
    }

    template<typename Collection, typename KeyProvider, typename Value>
    auto UpperBoundByKey(Collection& collection, const Value& value, const KeyProvider& keyProvider) {
        return UpperBoundByKey(collection.begin(), collection.end(), value, keyProvider);
    };
};

#endif //PITCHDETECTION_AZAZAI_ALGO_H
