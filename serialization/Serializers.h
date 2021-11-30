//
// Created by Semyon Tikhonenko on 5/26/21.
// Copyright (c) 2021 Semyon Tikhonenko. All rights reserved.
//

#ifndef VOCALTRAINER_SERIALIZERS_H
#define VOCALTRAINER_SERIALIZERS_H

#include "TypeTraits.h"
#include <stdint.h>
#include <vector>
#include <map>
#include <unordered_map>

static_assert(
        sizeof(int) == 4 &&
        sizeof(long long) == 8 &&
        sizeof(float) == 4 &&
        sizeof(double) == 8 &&
        sizeof(bool) == 1 &&
        sizeof(short) == 2,
        "Serialization is not supported by platform");

namespace CppUtils {
    namespace Serialization {
        template <
                typename T,
                typename Archive,
                typename = std::enable_if_t<std::is_arithmetic<T>::value>
        >
        void SaveOrLoad(T& o, Archive& archive, bool save) {
            archive.asRaw(o);
        }

        template<typename Archive>
        void SaveOrLoad(long& o, Archive& archive, bool save) {
            int64_t temp = o;
            archive.asRaw(temp);
            o = temp;
        }

        template<typename Archive>
        void SaveOrLoad(unsigned long& o, Archive& archive, bool save) {
            uint64_t temp = o;
            archive.asRaw(temp);
            o = temp;
        }

        template<typename Archive>
        void SaveOrLoad(long double& o, Archive& archive, bool save) {
            static_assert("Not supported");
        }

        template <typename T, typename Archive>
        auto SaveOrLoad(T& o, Archive& archive, bool save) -> typename std::enable_if<CppUtils::has_saveOrLoad<T, void(Archive&, bool)>::value, void>::type {
            o.saveOrLoad(archive, save);
        }

        // For classes with version
        template <typename T, typename Archive>
        auto SaveOrLoad(T& o, Archive& archive, bool save) -> typename std::enable_if<CppUtils::has_saveOrLoad<T, void(Archive&, bool, int)>::value, void>::type {
            int version = archive.template getSerializationVersion<T>();
            o.saveOrLoad(archive, save, version);
        }

        template <typename Container, typename Archive>
        void SaveOrLoadPrimitiveDataContainer(Container& o, Archive& archive) {
            int64_t size = o.size() * sizeof(typename Container::value_type);
            archive.asRaw(size);
            o.resize(size / sizeof(typename Container::value_type));
            archive.asBytes(o.data(), size);
        }

        template <typename Container, typename Archive>
        void SaveOrLoadArrayContainer(Container& o, Archive& archive) {
            int64_t size = o.size();
            archive.asRaw(size);
            o.resize(size);
            for (int i = 0; i < size; ++i) {
                archive(o[i]);
            }
        }

        template <typename Container, typename Archive>
        void SaveOrLoadInserterContainer(Container& container, Archive& archive, bool save) {
            int64_t size = container.size();
            archive.asRaw(size);
            if (save) {
                for (auto& o : container) {
                    archive(o);
                }
            } else {
                container.clear();
                for (int i = 0; i < size; ++i) {
                    typename Container::value_type value;
                    archive(value);
                    container.insert(container.end(), value);
                }
            }
        }

        template <typename Key, typename Value, typename Archive>
        void SaveOrLoad(std::pair<Key, Value>& pair, Archive& archive, bool save) {
            archive(const_cast<typename std::remove_const<Key>::type&>(pair.first));
            archive(pair.second);
        }

        template <typename Key, typename Value, typename Archive>
        void SaveOrLoad(std::map<Key, Value>& map, Archive& archive, bool save) {
            SaveOrLoadInserterContainer(map, archive, save);
        }

        template <typename Key, typename Value, typename Archive>
        void SaveOrLoad(std::unordered_map<Key, Value>& map, Archive& archive, bool save) {
            SaveOrLoadInserterContainer(map, archive, save);
        }

        template <typename T, typename Archive>
        auto SaveOrLoad(std::vector<T>& v, Archive& archive, bool save)
        -> typename std::enable_if<!std::is_arithmetic<T>::value, void>::type {
            SaveOrLoadArrayContainer(v, archive);
        }

        template <typename Char, typename Archive>
        auto SaveOrLoad(std::basic_string<Char>& str, Archive& archive, bool save)
        -> typename std::enable_if<
                std::is_same<Char, char>::value ||
                std::is_same<Char, char16_t>::value ||
                std::is_same<Char, char32_t>::value
        , void>::type {
            SaveOrLoadPrimitiveDataContainer(str, archive);
        }

        template <typename T, typename Archive>
        auto SaveOrLoad(std::vector<T>& v, Archive& archive, bool save)
        -> typename std::enable_if<
                std::is_arithmetic<T>::value
        , void>::type {
            SaveOrLoadPrimitiveDataContainer(v, archive);
        }
    }
};

#endif //VOCALTRAINER_SERIALIZERS_H
