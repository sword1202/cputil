//
// Created by Semyon Tikhonenko on 5/26/21.
// Copyright (c) 2021 Semyon Tikhonenko. All rights reserved.
//

#ifndef VOCALTRAINER_BINARYARCHIVE_H
#define VOCALTRAINER_BINARYARCHIVE_H

#include <stdint.h>
#include <iostream>
#include "Serializers.h"

namespace CppUtils {
    namespace Serialization {
        class BinaryWriteArchive {
            std::ostream& os;
        public:
            inline BinaryWriteArchive(std::ostream &os) : os(os) {
            }

            template <typename T>
            void operator()(T& o) {
                SaveOrLoad(o, *this, true);
            }

            template <typename T>
            void asRaw(T& o) {
                os.write(reinterpret_cast<const char*>(&o), sizeof(o));
            }

            inline void asBytes(void* buf, int64_t size) {
                os.write(reinterpret_cast<const char*>(buf), size);
            }
        };

        class BinaryReadArchive {
            std::istream& is;
        public:
            inline BinaryReadArchive(std::istream &is) : is(is) {
            }

            template <typename T>
            void operator()(T& o) {
                SaveOrLoad(o, *this, true);
            }

            template <typename T>
            void asRaw(T& o) {
                is.read(reinterpret_cast<char*>(&o), sizeof(o));
            }

            inline void asBytes(void* buf, int64_t size) {
                is.read(reinterpret_cast<char*>(buf), size);
            }
        };

        template <typename T>
        void WriteObjectToBinaryStream(const T& o, std::ostream& os) {
            BinaryWriteArchive archive(os);
            archive(const_cast<T&>(o));
        }

        template <typename T>
        void ReadObjectFromBinaryStream(T& o, std::istream& is) {
            BinaryReadArchive archive(is);
            archive(o);
        }
    }
}


#endif //VOCALTRAINER_BINARYARCHIVE_H
