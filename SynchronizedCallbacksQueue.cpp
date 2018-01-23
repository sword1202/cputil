//
// Created by Semyon Tikhonenko on 1/23/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#include "SynchronizedCallbacksQueue.h"

#define LOCK std::lock_guard<std::mutex> _(mutex)

using namespace CppUtils;

void SynchronizedCallbacksQueue::post(const Callback &callback) {
    LOCK;
    queue.push_back(callback);
}

void SynchronizedCallbacksQueue::process() {
    
    size_t size;
    {
        LOCK;
        size = queue.size();
    }

    for (int i = 0; i < size; ++i) {
        queue[i]();
    }

    auto begin = queue.begin();
    {
        LOCK;
        queue.erase(begin, begin + size);
    }
}
