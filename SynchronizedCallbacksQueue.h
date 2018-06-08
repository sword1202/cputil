//
// Created by Semyon Tikhonenko on 1/23/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_SYNCHRONIZEDQUEUE_H
#define VOCALTRAINER_SYNCHRONIZEDQUEUE_H

#include <functional>

#ifdef NO_BOOST
#include <vector>
#include <mutex>
#include <queue>
#else
#include <boost/lockfree/queue.hpp>
#endif

namespace CppUtils {

    class SynchronizedCallbacksQueue {
    public:
        typedef std::function<void()> Callback;
    private:
#ifdef NO_BOOST
        std::deque<Callback> queue;
        std::vector<Callback> threadSafeCopy;
        std::mutex mutex;
#else
        boost::lockfree::queue<Callback*, boost::lockfree::capacity<64>> queue;
#endif
    public:
        void post(const Callback &callback);
        void process();

#ifndef NO_BOOST
        ~SynchronizedCallbacksQueue();
#endif
    };

}


#endif //VOCALTRAINER_SYNCHRONIZEDQUEUE_H
