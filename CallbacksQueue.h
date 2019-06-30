//
// Created by Semyon Tikhonenko on 1/23/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_SYNCHRONIZEDQUEUE_H
#define VOCALTRAINER_SYNCHRONIZEDQUEUE_H

#include <functional>

#include <vector>
#include <mutex>
#include <queue>
#include <thread>

#include "DummyMutex.h"

#ifndef NDEBUG
#define CPPUTILS_CALLBACKS_QUEUE_DEBUG_INIT if (threadId == std::thread::id()) { \
    threadId = std::this_thread::get_id(); \
} \
if (std::is_same<Mutex, DummyMutex>::value) \
    assert(threadId == std::this_thread::get_id() && "Callbacks were posted or/and executed from different threads");
#else
#define CPPUTILS_CALLBACKS_QUEUE_DEBUG_INIT
#endif

namespace CppUtils {

    template <typename Mutex>
    class BaseCallbacksQueue {
    public:
        typedef std::function<void()> Callback;
    private:
        std::deque<Callback> queue;
        std::vector<Callback> threadSafeCopy;
        Mutex mutex;

#ifndef NDEBUG
        mutable std::thread::id threadId;
#endif

        template <typename Collection>
        void executeAll(const Collection& collection) {
            for (const Callback& callback : collection) {
                callback();
            }
        }
    public:
        void post(const Callback &callback) {
            CPPUTILS_CALLBACKS_QUEUE_DEBUG_INIT
            std::lock_guard<Mutex> _(mutex);
            queue.push_back(callback);
        }

        void process() {
            CPPUTILS_CALLBACKS_QUEUE_DEBUG_INIT
            if (std::is_same<Mutex, DummyMutex>::value) {
                executeAll(queue);
                queue.clear();
                return;
            }

            {
                std::lock_guard<Mutex> _(mutex);
                threadSafeCopy.assign(queue.begin(), queue.end());
            }

            executeAll(threadSafeCopy);

            {
                std::lock_guard<Mutex> _(mutex);
                auto begin = queue.begin();
                queue.erase(begin, begin + threadSafeCopy.size());
            }
        }
    };

    typedef BaseCallbacksQueue<DummyMutex> CallbacksQueue;
    typedef BaseCallbacksQueue<std::mutex> SynchronizedCallbacksQueue;
}


#endif //VOCALTRAINER_SYNCHRONIZEDQUEUE_H
