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

        template <typename Archive>
        void SaveOrLoad(int& o, Archive& archive, bool save) {
            if (save) {
                int64_t copy = o;
                archive(copy);
            } else {
                int64_t val = 0;
                archive(val);
                o = static_cast<int>(val);
            }
        }

        template <typename Archive>
        void SaveOrLoad(size_t& o, Archive& archive, bool save) {
            if (save) {
                uint64_t copy = o;
                archive(copy);
            } else {
                uint64_t val = 0;
                archive(val);
                o = static_cast<size_t>(val);
            }
        }

        template <typename Archive>
        void SaveOrLoad(unsigned int& o, Archive& archive, bool save) {
            if (save) {
                uint64_t copy = o;
                archive(copy);
            } else {
                uint64_t val = 0;
                archive(val);
                o = static_cast<unsigned int>(val);
            }
        }

        template <typename Archive>
        void SaveOrLoad(long& o, Archive& archive, bool save) {
            if (save) {
                int64_t copy = o;
                archive(copy);
            } else {
                int64_t val = 0;
                archive(val);
                o = static_cast<int>(val);
            }
        }

        template <typename T, typename Archive>
        auto SaveOrLoad(T& o, Archive& archive, bool save) -> typename std::enable_if<CppUtils::has_saveOrLoad<T, void(Archive&, bool)>::value, void>::type {
            o.saveOrLoad(archive, save);
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

        template <typename T, typename Archive>
        auto SaveOrLoad(std::vector<T>& v, Archive& archive, bool save)
        -> typename std::enable_if<!std::is_arithmetic<T>::value, void>::type {
            SaveOrLoadArrayContainer(v, archive);
        }

        template <typename Char, typename Archive>
        void SaveOrLoad(std::basic_string<Char>& str, Archive& archive, bool save) {
            SaveOrLoadPrimitiveDataContainer(str, archive);
        }

        template <typename T, typename Archive>
        auto SaveOrLoad(std::vector<T>& v, Archive& archive, bool save)
        -> typename std::enable_if<
                std::is_same<T, float>::value ||
                std::is_same<T, double>::value ||
                std::is_same<T, int32_t>::value ||
                std::is_same<T, int64_t>::value ||
                std::is_same<T, int16_t>::value ||
                std::is_same<T, int8_t>::value ||
                std::is_same<T, char>::value ||
                std::is_same<T, unsigned char>::value ||
                std::is_same<T, bool>::value ||
                std::is_same<T, short>::value ||
                std::is_same<T, uint32_t>::value ||
                std::is_same<T, uint64_t>::value ||
                std::is_same<T, uint16_t>::value ||
                std::is_same<T, uint8_t>::value
        , void>::type {
            SaveOrLoadPrimitiveDataContainer(v, archive);
        }
    }
};

#endif //VOCALTRAINER_SERIALIZERS_H
