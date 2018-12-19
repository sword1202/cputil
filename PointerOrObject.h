//
// Created by Semyon Tikhonenko on 2018-12-18.
//

#ifndef VOCALTRAINER_POINTERORORIGINAL_H
#define VOCALTRAINER_POINTERORORIGINAL_H

#include <type_traits>

// This type is a variant. It can hold a pointer to already allocated storage
// (also pointer to type allocated in a stack) or allocate its own storage
template<typename T>
class PointerOrObject {
    T* value = nullptr;
    bool isObject;
public:
    PointerOrObject() {
        isObject = false;
    }

    explicit PointerOrObject(const T *value) : value(const_cast<PointerOrObject*>(value)) {
        isObject = false;
    }

    explicit PointerOrObject(const T& value) {
        this->value = new T(value);
        isObject = true;
    }

    explicit PointerOrObject(T&& value) {
        this->value = new T(std::move(value));
        isObject = true;
    }

    PointerOrObject& operator=(const T& value) {
        if (isObject) {
            delete this->value;
        }

        this->value = new T(value);
        isObject = true;
        return *this;
    }

    PointerOrObject& operator=(const T* value) {
        if (isObject) {
            delete this->value;
        }

        this->value = const_cast<T*>(value);
        isObject = false;
        return *this;
    }

    T* operator->() {
        assert(isObject && "only originals can use non const -> operator");
        return value;
    }

    const T& operator*() const {
        if (!value) {
            return T();
        }

        return *value;
    }

    T& operator*() {
        if (!value) {
            value = new T();
            isObject = true;
        }

        assert(isObject && "only objects can use non const * operator");
        return *value;
    }

    const T* operator->() const {
        return value;
    }

    ~PointerOrObject() {
        if (isObject) {
            delete value;
        }
    }
};

#endif //VOCALTRAINER_POINTERORORIGINAL_H
