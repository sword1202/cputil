//
// Created by Semyon Tikhonenko on 8/7/16.
//

#ifndef PITCHDETECTION_AZAZAI_ALGO_H
#define PITCHDETECTION_AZAZAI_ALGO_H

#include <algorithm>
#include "StlDebugUtils.h"
#include <unordered_map>
#include <array>

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

    template<typename Collection, typename Value, typename KeyProvider>
    typename Collection::iterator FindLessOrEqualInSortedCollectionByKey(Collection& collection,
            const Value& value, const KeyProvider& keyProvider) {
        return FindLessOrEqualInSortedCollection(collection, value, [&] (const Value& a, const Value& b) {
            return keyProvider(a) < keyProvider(b);
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

    template<typename Iterator, typename KeyProvider>
    Iterator MaxByKey(Iterator begin, Iterator end, const KeyProvider& keyProvider) {
        return std::max_element(begin, end, [&keyProvider](const decltype(*begin)& a, const decltype(*begin)& b) {
            return keyProvider(a) < keyProvider(b);
        });
    }

    template<typename Collection, typename KeyProvider>
    auto MaxByKey(Collection& collection, const KeyProvider& keyProvider) {
        return MaxByKey(StlDebugUtils::begin(collection), StlDebugUtils::end(collection), keyProvider);
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
        return LowerBoundByKey(StlDebugUtils::begin(collection), StlDebugUtils::end(collection), value, keyProvider);
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
        return UpperBoundByKey(StlDebugUtils::begin(collection), StlDebugUtils::end(collection), value, keyProvider);
    };

    template<typename Iterator, typename KeyProvider>
    Iterator FindMinUsingKeyProvider(Iterator begin, Iterator end, const KeyProvider& keyProvider) {
        return std::min_element(begin, end, [&](const decltype(*begin)& a, const decltype(*begin)& b){
            return keyProvider(a) < keyProvider(b);
        });
    }

    template<typename Collection, typename KeyProvider>
    auto FindMinUsingKeyProvider(Collection& collection, const KeyProvider& keyProvider) {
        return FindMinUsingKeyProvider(StlDebugUtils::begin(collection), StlDebugUtils::end(collection), keyProvider);
    };

    template<typename Iterator, typename KeyProvider>
    const auto& FindMinValueUsingKeyProvider(Iterator begin, Iterator end, const KeyProvider& keyProvider) {
        assert(begin != end);
        return *std::min_element(begin, end, [&](const decltype(*begin)& a, const decltype(*begin) b){
            return keyProvider(a) < keyProvider(b);
        });
    }

    template<typename Collection, typename KeyProvider>
    const auto& FindMinValueUsingKeyProvider(const Collection& collection, const KeyProvider& keyProvider) {
        return FindMinValueUsingKeyProvider(StlDebugUtils::begin(collection), StlDebugUtils::end(collection),
                keyProvider);
    };

    template<typename Iterator, typename KeyProvider>
    std::pair<Iterator, Iterator> FindMinMaxUsingKeyProvider(Iterator begin, Iterator end, const KeyProvider& keyProvider) {
        return std::minmax_element(begin, end, [&](const decltype(*begin)& a, const decltype(*begin)& b){
            return keyProvider(a) < keyProvider(b);
        });
    }

    template<typename Collection, typename KeyProvider>
    auto FindMinMaxUsingKeyProvider(const Collection& collection, const KeyProvider& keyProvider) {
        return FindMinMaxUsingKeyProvider(collection.begin(), collection.end(),
                keyProvider);
    }


    template<typename Collection, typename Predicate>
    int FindIndex(const Collection& collection, const Predicate& predicate) {
        for (int i = 0; i < collection.size(); ++i) {
            if (predicate(collection[i])) {
                return i;
            }
        }

        return -1;
    }

    template<typename Collection, typename Predicate>
    std::vector<int> FindIndexes(const Collection& collection, const Predicate& predicate) {
        std::vector<int> result;

        for (int i = 0; i < collection.size(); ++i) {
            if (predicate(collection[i])) {
                result.push_back(i);
            }
        }

        return result;
    }

    template<typename Iterator, typename Predicate>
    bool Contains(Iterator begin, Iterator end, const Predicate& predicate) {
        for (auto iter = begin; iter != end; ++iter) {
            if (predicate(*iter)) {
                return true;
            }
        }

        return false;
    }

    template<typename Collection, typename Predicate>
    bool Contains(const Collection& collection, const Predicate& predicate) {
        return Contains(collection.begin(), collection.end(), predicate);
    }


    template<typename Collection, typename Predicate>
    bool ContainsIndex(const Collection& collection, const Predicate& predicate) {
        for (int i = 0; i < collection.size(); ++i) {
            if (predicate(i)) {
                return true;
            }
        }

        return false;
    }

    template <typename Map, typename Iter>
    void FillCountingMap(Map* map, Iter begin, Iter end) {
        std::for_each(begin, end, [=] (const auto& value) {
            ++map[value];
        });
    };

    template<typename Iter1, typename Iter2>
    bool ContentEqualsAnyOrderUsingHash(Iter1 begin, Iter1 end, Iter2 begin2, Iter2 end2) {
        std::unordered_map<decltype(*begin), int> map1;
        std::unordered_map<decltype(*begin2), int> map2;

        FillCountingMap(&map1, begin, end);
        FillCountingMap(&map2, begin2, end2);

        return std::all_of(map1.begin(), map1.end(), [&] (const auto& pair) {
            return map2[pair.first] == pair.second;
        });
    }

    template<typename Collection1, typename Collection2>
    bool ContentEqualsAnyOrderUsingHash(const Collection1& collection1, const Collection2& collection2) {
        return ContentEqualsAnyOrderUsingHash(collection1.begin(), collection1.end(),
                collection2.begin(), collection2.end());
    };

    template<typename T1, int N>
    bool ArrayEqualsAnyOrderUsingHash(const std::array<T1, N>& collection1, const std::array<T1, N>& collection2) {
        return ContentEqualsAnyOrderUsingHash(collection1, collection2);
    };
}

#endif //PITCHDETECTION_AZAZAI_ALGO_H
