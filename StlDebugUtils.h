//
// Created by Semyon Tikhonenko on 4/28/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_STLDEBUGUTILS_H
#define VOCALTRAINER_STLDEBUGUTILS_H

#include <assert.h>

#include "stlassert.h"

#include <vector>

namespace CppUtils {

    namespace StlDebugUtils {
#ifdef DEBUG

        template<typename T>
        class vector_iterator {
            int index = 0;
            int size;
            std::vector<T> *vector;
            typename std::vector<T>::iterator iter;
        public:

            typedef std::random_access_iterator_tag iterator_category;
            typedef int   difference_type;
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;

            vector_iterator(typename std::vector<T>::iterator iter, int index, std::vector<T> *vector)
                    : index(index), iter(iter), vector(vector), size(vector->size()) {
            }

            bool operator==(const vector_iterator &rhs) const {
                assert(vector == rhs.vector);
                return iter == rhs.iter;
            }

            bool operator!=(const vector_iterator &rhs) const {
                assert(vector == rhs.vector);
                return !(rhs == *this);
            }

            T &operator*() {
                assert(size == vector->size());
                assert(index < size);
                return *iter;
            }

            T* operator->() {
                assert(size == vector->size());
                assert(index < size);
                return &*iter;
            }

            vector_iterator &operator++() {
                assert(size == vector->size());
                index++;
                iter++;
                return *this;
            }

            vector_iterator operator++(int) {
                assert(size == vector->size());
                auto res = *this;
                index++;
                iter++;
                return res;
            }

            vector_iterator &operator--() {
                assert(size == vector->size());
                index--;
                iter--;
                return *this;
            }

            vector_iterator &operator--(int) {
                assert(size == vector->size());
                auto res = *this;
                index--;
                iter--;
                return res;
            }

            vector_iterator &operator+=(int value) {
                assert(size == vector->size());
                index += value;
                iter += value;
                return *this;
            }

            vector_iterator &operator-=(int value) {
                assert(size == vector->size());
                index -= value;
                iter -= value;
                return *this;
            }

            vector_iterator operator+(int value) const {
                assert(size == vector->size());
                return vector_iterator(iter + value, index + value, vector);
            }

            vector_iterator operator-(int value) const {
                assert(size == vector->size());
                return vector_iterator(iter - value, index - value, vector);
            }

            int operator-(const vector_iterator &value) const {
                assert(size == vector->size());
                assert(value.vector == vector);
                return index - value.index;
            }

            T& operator[](int i) {
                assert(size == vector->size());
                assert(index + i < size && index - i >= 0);
                return iter[i];
            }
        };

        template<typename T>
        class vector_const_iterator {
            int index = 0;
            int size;
            const std::vector<T> *vector;
            typename std::vector<T>::const_iterator iter;
        public:
            typedef std::random_access_iterator_tag iterator_category;
            typedef int   difference_type;
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;

            vector_const_iterator(typename std::vector<T>::const_iterator iter, int index, const std::vector<T> *vector)
                    : index(index), iter(iter), vector(vector), size(vector->size()) {
            }

            bool operator==(const vector_const_iterator &rhs) const {
                assert(vector == rhs.vector);
                return iter == rhs.iter;
            }

            bool operator!=(const vector_const_iterator &rhs) const {
                assert(vector == rhs.vector);
                return !(rhs == *this);
            }

            const T &operator*() const {
                assert(size == vector->size());
                assert(index < size);
                return *iter;
            }

            const T* operator->() const {
                assert(size == vector->size());
                assert(index < size);
                return &*iter;
            }

            vector_const_iterator &operator++() {
                assert(size == vector->size());
                index++;
                iter++;
                return *this;
            }

            vector_const_iterator operator++(int) {
                assert(size == vector->size());
                auto res = *this;
                index++;
                iter++;
                return res;
            }

            vector_const_iterator &operator--() {
                assert(size == vector->size());
                index--;
                iter--;
                return *this;
            }

            vector_const_iterator &operator--(int) {
                assert(size == vector->size());
                auto res = *this;
                index--;
                iter--;
                return res;
            }

            vector_const_iterator &operator+=(int value) {
                assert(size == vector->size());
                index += value;
                iter += value;
                return *this;
            }

            vector_const_iterator &operator-=(int value) {
                assert(size == vector->size());
                index -= value;
                iter -= value;
                return *this;
            }

            vector_const_iterator operator+(int value) const {
                assert(size == vector->size());
                return vector_const_iterator(iter + value, index + value, vector);
            }

            vector_const_iterator operator-(int value) const {
                assert(size == vector->size());
                return vector_const_iterator(iter - value, index - value, vector);
            }

            int operator-(const vector_const_iterator &value) const {
                assert(value.vector == vector);
                return index - value.index;
            }

            const T& operator[](int i) const {
                assert(size == vector->size());
                assert(index + i < size && index - i >= 0);
                return iter[i];
            }
        };

        template<typename T>
        vector_iterator<T> begin(std::vector<T> &vector) {
            return vector_iterator<T>(vector.begin(), 0, &vector);
        }

        template<typename T>
        vector_iterator<T> end(std::vector<T> &vector) {
            return vector_iterator<T>(vector.end(), vector.size(), &vector);
        }

        template<typename T>
        vector_const_iterator<T> begin(const std::vector<T> &vector) {
            return vector_const_iterator<T>(vector.begin(), 0, &vector);
        }

        template<typename T>
        vector_const_iterator<T> end(const std::vector<T> &vector) {
            return vector_const_iterator<T>(vector.end(), vector.size(), &vector);
        }

#else
        // TODO: add release support
        template <typename T>
        using vector_iterator = std::vector<T>::iterator;
    
        template <typename T>
        using vector_const_iterator = std::vector<T>::const_iterator;
    
            template<typename T>
        vector_iterator<T> begin(std::vector<T>& vector) {
            return vector.begin();
        }
    
        template<typename T>
        vector_iterator<T> end(std::vector<T>& vector) {
            return vector.end();
        }
    
        template<typename T>
        vector_const_iterator<T> begin(const std::vector<T>& vector) {
            return vector.begin();
        }
    
        template<typename T>
        vector_const_iterator<T> end(const std::vector<T>& vector) {
            return vector.end();
        }
#endif

        template<typename Collection>
        typename Collection::iterator begin(Collection& collection) {
            return collection.begin();
        }

        template<typename Collection>
        typename Collection::const_iterator begin(const Collection& collection) {
            return collection.begin();
        }

        template<typename Collection>
        typename Collection::iterator end(Collection& collection) {
            return collection.end();
        }

        template<typename Collection>
        typename Collection::const_iterator end(const Collection& collection) {
            return collection.end();
        }
    }
}

#endif //VOCALTRAINER_STLDEBUGUTILS_H
