//
// Created by Semyon Tikhonenko on 8/7/16.
//

#ifndef PITCHDETECTION_AZAZAI_ALGO_H
#define PITCHDETECTION_AZAZAI_ALGO_H

#include <algorithm>
#include "StlDebugUtils.h"
#include <unordered_map>
#include <array>
#include <numeric>

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
    typename Collection::const_iterator FindLessInSortedCollection(const Collection& collection,
                                                             const Value& value) {
        auto iter = std::upper_bound(collection.begin(), collection.end(), value);
        if(iter == collection.begin() || collection.begin() == collection.end()) {
            return collection.end();
        }

        return --iter;
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

    template<typename Iterator, typename KeyProvider>
    Iterator MinByKey(Iterator begin, Iterator end, const KeyProvider& keyProvider) {
        return std::min_element(begin, end, [&keyProvider](const decltype(*begin)& a, const decltype(*begin)& b) {
            return keyProvider(a) < keyProvider(b);
        });
    }

    template<typename Collection, typename KeyProvider>
    auto MinByKey(Collection& collection, const KeyProvider& keyProvider) {
        return MinByKey(StlDebugUtils::begin(collection), StlDebugUtils::end(collection), keyProvider);
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

    template<typename Collection>
    int FindIndex(const Collection& collection, const decltype(collection[0])& value) {
        for (int i = 0; i < collection.size(); ++i) {
            if (collection[i] == value) {
                return i;
            }
        }

        return -1;
    }

    template<typename Collection, typename Predicate>
    const typename Collection::value_type* Find(const Collection& collection, const Predicate& predicate) {
        auto iter = std::find_if(collection.begin(), collection.end(), predicate);
        if (iter != collection.end()) {
            return &*iter;
        } else {
            return nullptr;
        }
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

    template<typename Collection>
    bool ContainsValue(const Collection& collection, const typename Collection::value_type& value) {
        return Contains(collection.begin(), collection.end(), [&] (const auto& v) {
            return value == v;
        });
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

    template <typename Collection, typename Item>
    void Remove(Collection& collection, const Item& item) {
        for (auto iter = collection.begin(); iter != collection.end(); ++iter) {
            if (*iter == item) {
                collection.erase(iter);
            }
        }
    }

    template <typename Collection, typename Predicate>
    void RemoveIf(Collection& collection, const Predicate& predicate) {
        for (auto iter = collection.begin(); iter != collection.end(); ++iter) {
            if (predicate(*iter)) {
                collection.erase(iter);
            }
        }
    }

    template <typename Map, typename Iter>
    void FillCountingMap(Map* map, Iter begin, Iter end) {
        std::for_each(begin, end, [=] (const auto& value) {
            ++map[value];
        });
    };

    template <typename Collection, typename T>
    void Fill(Collection* collection, const T& value) {
        std::fill(collection->begin(), collection->end(), value);
    }

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

    template<typename To, typename From, typename Function>
    To Transform(const From& from, const Function& func) {
        To to;
        auto iter = std::back_inserter(to);
        for (const auto& value : from) {
            *iter++ = func(value);
        }

        return to;
    }

    template<typename To, typename From, typename Function>
    void Transform(const From& from, To* to, const Function& func) {
        auto iter = std::back_inserter(*to);
        for (const auto& value : from) {
            *iter++ = func(value);
        }

        return to;
    }

    template<typename Result, typename T>
    Result Sum(const T* data, int size) {
        return std::accumulate(data, data + size, Result());
    }

    template<typename Result, typename T, typename Transformer>
    Result Sum(const T* data, int size, const Transformer& transformer, Result initialValue = Result()) {
        for (int i = 0; i < size; ++i) {
            initialValue += transformer(data[i]);
        }

        return initialValue;
    }

    template<typename Result, typename Container, typename Transformer>
    auto Sum(const Container& data, const Transformer& transformer,
            Result initialValue = Result()) {
        for (const auto& o : data) {
            initialValue += transformer(o);
        }

        return initialValue;
    }

    template<typename Result, typename T>
    Result AbsoluteSum(const T* data, int size) {
        return Sum<Result>(data, size, [] (T value) {
            return abs(value);
        });
    }

    template<typename Result, typename T>
    Result AbsoluteAverage(const T* data, int size) {
        return AbsoluteSum<Result>(data, size) / (Result)size;
    }

    template<typename Result, typename T>
    Result Average(const T* data, int size) {
        return Sum<Result>(data, size) / (Result)size;
    }

    template <typename Collection>
    void EraseRange(Collection& collection, int begin, int excludedEnd) {
        assert(begin <= excludedEnd);
        auto iterBegin = collection.begin() + begin;
        auto iterEnd = collection.begin() + excludedEnd;
        collection.erase(iterBegin, iterEnd);
    }

    template <typename Collection>
    void EraseEndingOfCollection(Collection &collection, int begin) {
        int end = collection.size();
        EraseRange(collection, begin, end);
    }


    template <typename Collection, typename Value>
    std::pair<typename Collection::const_iterator, typename Collection::const_iterator>
            FindRangeInSortedCollection(const Collection& collection, const Value& a, const Value& b) {
        auto begin = std::lower_bound(collection.begin(), collection.end(), a);
        auto end = std::upper_bound(collection.begin(), collection.end(), b);

        if (end - begin <= 0) {
            return std::make_pair(collection.end(), collection.end());
        }

        return std::make_pair(begin, end);
    }

    template <typename Collection, typename Value>
    void GetItemsInRangeInSortedCollection(
            const Collection& collection,
            const Value& a,
            const Value& b,
            std::vector<Value>* out) {
        auto itersRange = FindRangeInSortedCollection(collection, a, b);
        out->resize(itersRange.second - itersRange.first);
        std::copy(itersRange.first, itersRange.second, out->begin());
    }

    template<typename Container, typename Predicate>
    std::vector<typename Container::value_type> Filter(const Container& container, const Predicate& predicate) {
        std::vector<typename Container::value_type> result;
        for (const auto& value : container) {
            if (predicate(value)) {
                result.push_back(value);
            }
        }

        return result;
    }

    template<typename Container, typename Predicate, typename InsertionContainer>
    bool InsertAfter(Container* container, const Predicate& predicate, const InsertionContainer& insertionContainer) {
        auto iter = std::find_if(container->begin(), container->end(), predicate);
        if (iter == container->end()) {
            return false;
        }

        container->insert(++iter, insertionContainer.begin(), insertionContainer.end());
        return true;
    }

    template <typename Container1, typename Container2>
    bool Equal(const Container1& a, const Container2& b) {
        return a.size() == b.size()
        && std::equal(a.begin(), a.end(), b.begin());
    }

    // Callback -> func(const T* current, const T* prev)
    template <typename Container, typename Callback>
    void IteratePassingPrevElement(const Container& container, const Callback& callback) {
        if (container.empty()) {
            return;
        }

        if (container.size() == 1) {
            callback(&*container.begin(), nullptr);
        }

        auto prev = container.begin();
        auto iter = prev;
        callback(&*iter, nullptr);
        ++iter;
        while (iter != container.end()) {
            callback(&*iter, &*prev);
            prev = iter;
            ++iter;
        }
    }

    // Callback -> func(const T* current, const T* prev)
    template <typename Container, typename Callback>
    void IteratePassingNextElement(const Container& container, const Callback& callback) {
        if (container.empty()) {
            return;
        }

        if (container.size() == 1) {
            callback(&*container.begin(), nullptr);
        }

        auto current = container.begin();
        auto next = ++current;
        while (next != container.end()) {
            callback(&*current, &*next);
            current = next;
            ++next;
        }

        callback(&*current, nullptr);
    }

    template <typename Collection, typename Predicate>
    auto RemoveDuplicatesInSortedCollection(const Collection& collection, const Predicate& predicate) -> std::vector<typename Collection::value_type> {
        std::vector<typename Collection::value_type> result;
        const typename Collection::value_type* lastValue = nullptr;
        for (const auto& value : collection) {
            if (!lastValue || !predicate(*lastValue, value)) {
                result.push_back(value);
                lastValue = &value;
            }
        }

        return result;
    }
}

#endif //PITCHDETECTION_AZAZAI_ALGO_H
