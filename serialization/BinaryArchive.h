//
// Created by Semyon Tikhonenko on 5/26/21.
// Copyright (c) 2021 Semyon Tikhonenko. All rights reserved.
//

#ifndef VOCALTRAINER_BINARYARCHIVE_H
#define VOCALTRAINER_BINARYARCHIVE_H

#include <stdint.h>
#include <iostream>
#include "Serializers.h"
#include "Maps.h"

#ifndef NDEBUG
#include <typeinfo>
#endif

namespace CppUtils {
    namespace Serialization {
        class BinaryWriteArchive {
            std::ostream& os;
            std::stringstream temp;
            std::ostream* activeStream;
            std::unordered_map<int, int> versionsMap;
#ifndef NDEBUG
            // Used only for debug purposes
            std::unordered_map<int, const std::type_info*> serializationIdTypeInfoMap;
#endif
        public:
            inline BinaryWriteArchive(std::ostream &os) : os(os) {
                activeStream = &temp;
            }

            template <typename T>
            void operator()(T& o) {
                SaveOrLoad(o, *this, true);
            }

            template <typename T>
            void asRaw(T& o) {
                activeStream->write(reinterpret_cast<const char*>(&o), sizeof(o));
            }

            inline void asBytes(void* buf, int64_t size) {
                activeStream->write(reinterpret_cast<const char*>(buf), size);
            }

            template <typename T>
            int getSerializationVersion() {
                versionsMap[T::SERIALIZATION_ID] = T::VERSION;
#ifndef NDEBUG
                // Check there are no same serializationIdes for different types
                auto iter = serializationIdTypeInfoMap.find(T::SERIALIZATION_ID);
                assert((iter == serializationIdTypeInfoMap.end() || iter->second == &typeid(T))  && "Duplicated version ides");
                serializationIdTypeInfoMap[T::SERIALIZATION_ID] = &typeid(T);
#endif
                return T::VERSION;
            }

            void flush() {
                activeStream = &os;
                (*this)(versionsMap);
                os << temp.rdbuf();
            }
        };

        class BinaryReadArchive {
            std::istream& is;
            std::unordered_map<int, int> versionsMap;
        public:
            inline BinaryReadArchive(std::istream &is) : is(is) {
                (*this)(versionsMap);
            }

            template <typename T>
            void operator()(T& o) {
                SaveOrLoad(o, *this, false);
            }

            template <typename T>
            void asRaw(T& o) {
                is.read(reinterpret_cast<char*>(&o), sizeof(o));
            }

            inline void asBytes(void* buf, int64_t size) {
                is.read(reinterpret_cast<char*>(buf), size);
            }

            template <typename T>
            int getSerializationVersion() {
                return versionsMap[T::SERIALIZATION_ID];
            }
        };

        template <typename T>
        void WriteObjectToBinaryStream(const T& o, std::ostream& os) {
            BinaryWriteArchive archive(os);
            archive(const_cast<T&>(o));
            archive.flush();
        }

        template <typename T>
        void ReadObjectFromBinaryStream(T& o, std::istream& is) {
            BinaryReadArchive archive(is);
            archive(o);
        }
    }
}


#endif //VOCALTRAINER_BINARYARCHIVE_H
