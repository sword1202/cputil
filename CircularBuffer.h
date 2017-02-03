//
// Created by Semyon Tikhonenko on 1/25/17.
//

#ifndef PITCHDETECTION_CIRCULARBUFFER_H
#define PITCHDETECTION_CIRCULARBUFFER_H

#include <vector>
#include <deque>

namespace Azazai {
template<typename T>
class CircularBuffer {
public:
    CircularBuffer(size_t maxSize) {
        this->maxSize = maxSize;
    }

    void push_back(T item) {
        if (deque.size() == maxSize) {
            deque.pop_front();
        }

        deque.push_back(item);
    }

    const T& front() const {
        return deque.front();
    }

    size_t size() const {
        return deque.size();
    }

    size_t capacity() const {
        return maxSize;
    }
private:
    std::deque<T> deque;
    size_t maxSize;
};
}

#endif //PITCHDETECTION_CIRCULARBUFFER_H
