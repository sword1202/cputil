//
// Created by Semyon Tikhonenko on 5/4/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_LISTENERSSET_H
#define VOCALTRAINER_LISTENERSSET_H

#include <functional>
#include <map>

namespace CppUtils {
    enum ListenerAction {
        DONT_DELETE_LISTENER,
        DELETE_LISTENER
    };

    template<typename... Args>
    class ListenersSet {
    public:

        typedef std::function<ListenerAction(Args...)> function;
    private:
        std::map<int, function> listeners;
        int nextKey = 0;
    public:
        int addListener(const function &func) {
            int key = nextKey++;
            listeners[key] = func;

            return key;
        }

        void removeListener(int key) {
            size_t numberOfElementsRemoved = listeners.erase(key);
            assert(numberOfElementsRemoved == 1);
        }

        void executeAll(Args... args) {
            for (auto iter = listeners.begin(); iter != listeners.end();) {
                if (iter->second(args...) == DELETE_LISTENER) {
                    iter = listeners.erase(iter);
                } else {
                    ++iter;
                }
            }
        }

        bool hasListenersToExecute() const {
            return !listeners.empty();
        }
    };

}


#endif //VOCALTRAINER_LISTENERSSET_H
