//
// Created by Semyon Tikhonenko on 1/23/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#include "SynchronizedCallbacksQueue.h"

using namespace CppUtils;

#ifdef NO_BOOST

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

#else

#include <boost/lockfree/queue.hpp>
#include <boost/pool/pool_alloc.hpp>

static boost::fast_pool_allocator<SynchronizedCallbacksQueue::Callback> allocator;

void SynchronizedCallbacksQueue::post(const Callback &callback) {
    Callback* copy = allocator.allocate();
    allocator.construct(copy, callback);
    queue.push(copy);
}

void SynchronizedCallbacksQueue::process() {
    Callback* callback;
    while (queue.pop(callback)) {
        (*callback)();
        delete callback;
    }
}

SynchronizedCallbacksQueue::~SynchronizedCallbacksQueue() {
    Callback* callback;
    while (queue.pop(callback)) {
        allocator.destroy(callback);
        allocator.deallocate(callback);
    }
}

#endif
