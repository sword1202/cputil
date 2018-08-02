//
// Created by Semyon Tikhonenko on 5/4/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_LISTENERSSET_H
#define VOCALTRAINER_LISTENERSSET_H

#include <functional>
#include <map>
#include <numeric>
#include "assert.h"

#ifndef NDEBUG
#include <thread>

#define CPPUTILS_LISTENERS_SET_DEBUG_INIT if (threadId == std::thread::id()) { \
    threadId = std::this_thread::get_id(); \
} \
assert(threadId == std::this_thread::get_id() && "Listeners were added or/and executed or/and removed from different threads");
#else
#define CPPUTILS_LISTENERS_SET_DEBUG_INIT
#endif

namespace CppUtils {
    enum ListenerAction {
        DONT_DELETE_LISTENER,
        DELETE_LISTENER
    };

    template<typename... Args>
    class ListenersSet {
    public:
        typedef std::function<ListenerAction(Args...)> Listener;
    private:
        std::map<int, Listener> listeners;
        int nextKey = 1;
#ifndef NDEBUG
        mutable std::thread::id threadId;
#endif
    public:
        int addListener(const Listener &func) {
            CPPUTILS_LISTENERS_SET_DEBUG_INIT

            int key = nextKey++;
            listeners[key] = func;

            return key;
        }

        int addHighPriorityListener(const Listener &func) {
            CPPUTILS_LISTENERS_SET_DEBUG_INIT
            int key = listeners.begin()->first - 1;
            if (key == 0) {
                key--;
            }

            listeners[key] = func;

            return key;
        }

        bool removeListener(int key) {
            CPPUTILS_LISTENERS_SET_DEBUG_INIT
            return (bool)listeners.erase(key);
        }

        void executeAll(Args... args) {
            CPPUTILS_LISTENERS_SET_DEBUG_INIT

            auto end = listeners.end();
            for (auto iter = listeners.begin(); iter != end;) {
                if (iter->second(args...) == DELETE_LISTENER) {
                    iter = listeners.erase(iter);
                } else {
                    ++iter;
                }
            }
        }

        bool hasListenersToExecute() const {
            CPPUTILS_LISTENERS_SET_DEBUG_INIT
            return !listeners.empty();
        }
    };
}

#define CPPUTILS_DEFINE_LISNERS_SET()


#endif //VOCALTRAINER_LISTENERSSET_H
