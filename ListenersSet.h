//
// Created by Semyon Tikhonenko on 5/4/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_LISTENERSSET_H
#define VOCALTRAINER_LISTENERSSET_H

#include <functional>
#include <map>
#include <numeric>

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
    public:
        int addListener(const Listener &func) {
            int key = nextKey++;
            listeners[key] = func;

            return key;
        }

        int addHighPriorityListener(const Listener &func) {
            int key = listeners.begin()->first - 1;
            if (key == 0) {
                key--;
            }

            listeners[key] = func;

            return key;
        }

        bool removeListener(int key) {
            return (bool)listeners.erase(key);
        }

        void executeAll(Args... args) {
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
            return !listeners.empty();
        }
    };

}


#endif //VOCALTRAINER_LISTENERSSET_H
