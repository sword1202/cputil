//
// Created by Semyon Tikhonenko on 1/23/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#include "SynchronizedCallbacksQueue.h"

using namespace CppUtils;

#define LOCK std::lock_guard<std::mutex> _(mutex)

void SynchronizedCallbacksQueue::post(const Callback &callback) {
    LOCK;
    queue.push_back(callback);
}

void SynchronizedCallbacksQueue::process() {
    {
        LOCK;
        threadSafeCopy.assign(queue.begin(), queue.end());
    }

    for (const Callback& callback : threadSafeCopy) {
        callback();
    }

    {
        LOCK;
        auto begin = queue.begin();
        queue.erase(begin, begin + threadSafeCopy.size());
    }
}
