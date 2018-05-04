//
// Created by Semyon Tikhonenko on 5/4/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_LISTENERSSET_H
#define VOCALTRAINER_LISTENERSSET_H

#include <functional>
#include <map>

namespace CppUtils {

template<typename... Args>
class ListenersSet {
public:
    typedef std::function<void(Args...)> function;
private:
    std::map<int, function> listeners;
public:
    int addListener(const function &func) {
        int key = 0;
        auto rbegin = listeners.rbegin();
        if (rbegin != listeners.rend()) {
            key = rbegin->first;
        }
        listeners[key] = func;

        return key;
    }

    int addOneShotListener(function func) {
        int key = 0;
        auto rbegin = listeners.rbegin();
        if (rbegin != listeners.rend()) {
            key = rbegin->first;
        }

        func = [=](Args... args) {
            func(args);
            listeners.erase(key);
        };

        listeners[key] = func;

        return key;
    }

    void removeListener(int key) {
        size_t numberOfElementsRemoved = listeners.erase(key);
        assert(numberOfElementsRemoved == 1);
    }

    void executeAll(Args... args) {
        for (const auto& pair : listeners) {
            pair.second(args...);
        }
    }
};

}


#endif //VOCALTRAINER_LISTENERSSET_H
