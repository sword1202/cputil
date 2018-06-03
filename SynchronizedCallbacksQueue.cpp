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
    {
        threadSafeCopy.assign(queue.begin(), queue.end());
        LOCK;
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
