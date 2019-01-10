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

namespace CppUtils {

    class SynchronizedCallbacksQueue {
    public:
        typedef std::function<void()> Callback;
    private:
        std::deque<Callback> queue;
        std::vector<Callback> threadSafeCopy;
        std::mutex mutex;
    public:
        void post(const Callback &callback);
        void process();
    };

}


#endif //VOCALTRAINER_SYNCHRONIZEDQUEUE_H
