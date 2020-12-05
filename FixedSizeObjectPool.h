//
// Created by Semyon Tikhonenko on 12/1/20.
// Copyright (c) 2020 Semyon Tikhonenko. All rights reserved.
//

#ifndef VOCALTRAINER_FIXEDSIZEOBJECTPOOL_H
#define VOCALTRAINER_FIXEDSIZEOBJECTPOOL_H

#include <vector>
#include "Algorithms.h"

namespace CppUtils {
    template <typename T>
    class FixedSizeObjectPool {
        std::vector<bool> availableObjects;
        std::vector<T> pool;
    public:
        void init(size_t count, const T& obj) {
            assert(count >= 0);
            pool.assign(count, obj);
            availableObjects.assign(count, true);
        }

        T* tryGetObject() {
            for (int i = 0; i < availableObjects.size(); ++i) {
                if (availableObjects[i]) {
                    availableObjects[i] = false;
                    return &pool[i];
                }
            }

            return nullptr;
        }

        T* getObject() {
            T* object = tryGetObject();
            assert(object && "All objects in the pool are occupied");
            return object;
        }

        void returnObject(const T* object) {
            int index = FindIndex(pool, [=] (const T& value) {
                return object == &value;
            });
            assert(index >= 0 && "Trying to return an object, which is not from this pool");
            availableObjects[index] = true;
        }

        void returnAll() {
            std::fill(availableObjects.begin(), availableObjects.end(), true);
        }
    };
}


#endif //VOCALTRAINER_FIXEDSIZEOBJECTPOOL_H
