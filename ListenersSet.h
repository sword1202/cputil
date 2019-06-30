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
#include <mutex>
#include "Maps.h"
#include "Algorithms.h"
#include "DummyMutex.h"
#include "DestructorQueue.h"

#ifndef NDEBUG
#include <thread>
#include <type_traits>

#define CPPUTILS_LISTENERS_SET_DEBUG_INIT if (threadId == std::thread::id()) { \
    threadId = std::this_thread::get_id(); \
} \
if (std::is_same<Mutex, DummyMutex>::value) \
    assert(threadId == std::this_thread::get_id() && "Listeners were added or/and executed or/and removed from different threads");
#else
#define CPPUTILS_LISTENERS_SET_DEBUG_INIT
#endif

namespace CppUtils {
    enum ListenerAction {
        DONT_DELETE_LISTENER,
        DELETE_LISTENER
    };

    template<typename Mutex, typename... Args>
    class BaseListenersSet {
    public:
        typedef std::function<ListenerAction(Args...)> Listener;
    private:
        typedef std::map<int, Listener> Map;
        Mutex mutex;
        Map listeners;
        std::map<void*, int> functionPointerListenersMap;
        int nextKey = 1;
#ifndef NDEBUG
        mutable std::thread::id threadId;

        bool checkThereIsNoKeyInFunctionPointerListenersMap(int key) const {
            auto values = Maps::Values(functionPointerListenersMap);
            return !ContainsValue(values, key);
        }
#endif

        template <typename Function>
        void addFunctionalPointerListener(Function *func, ListenerAction listenerAction,
                AbstractDestructorQueue *parent = nullptr) {
            {
                std::lock_guard<Mutex> _(mutex);
                if (functionPointerListenersMap.count(func)) {
                    return;
                }
            }

            int key = addListenerWithAction(Listener([=] (Args... args) -> ListenerAction {
                (*func)(args...);
                return listenerAction;
            }));

            if (parent) {
                parent->executeOnDestructor([=] {
                    removeListener(func);
                });
            }

            std::lock_guard<Mutex> _(mutex);
            functionPointerListenersMap[func] = key;
        }

    public:
        // Removes the listener automatically, when parent is destroyed
        int addListenerWithAction(const Listener &func, AbstractDestructorQueue* parent = nullptr) {
            CPPUTILS_LISTENERS_SET_DEBUG_INIT

            int key;
            {
                std::lock_guard<Mutex> _(mutex);
                key = nextKey++;
                listeners[key] = func;
            }

            if (parent) {
                parent->executeOnDestructor([=] {
                    removeListener(key);
                });
            }

            return key;
        }

        template <typename Function>
        int addListener(const Function& func, AbstractDestructorQueue* parent = nullptr) {
            return addListenerWithAction(Listener([=] (Args... args) -> ListenerAction {
                func(args...);
                return DONT_DELETE_LISTENER;
            }), parent);
        }

        template <typename Function>
        void addListener(Function* func, AbstractDestructorQueue* parent = nullptr) {
            addFunctionalPointerListener(func, DONT_DELETE_LISTENER, parent);
        }

        template <typename Function>
        int addOneShotListener(const Function& func, AbstractDestructorQueue* parent = nullptr) {
            return addListenerWithAction(Listener([=] (Args... args) -> ListenerAction {
                func(args...);
                return DELETE_LISTENER;
            }), parent);
        }

        template <typename Function>
        void addOneShotListener(Function* func, AbstractDestructorQueue* parent = nullptr) {
            addFunctionalPointerListener(func, DELETE_LISTENER);
        }

        bool removeListener(int key) {
            CPPUTILS_LISTENERS_SET_DEBUG_INIT
            std::lock_guard<Mutex> _(mutex);
            assert(checkThereIsNoKeyInFunctionPointerListenersMap(key) && "trying to delete pointer to functional "
                                                                          "object through key");
            return (bool)listeners.erase(key);
        }

        bool removeListener(void* functionalObjectPointer) {
            CPPUTILS_LISTENERS_SET_DEBUG_INIT
            std::lock_guard<Mutex> _(mutex);
            auto iter = functionPointerListenersMap.find(functionalObjectPointer);
            if (iter == functionPointerListenersMap.end()) {
                return false;
            }

            int key = iter->second;
            functionPointerListenersMap.erase(iter);
            return (bool)listeners.erase(key);
        }

        template<typename Arg, typename... Args2>
        void removeListeners(Arg arg, Args2... args) {
            removeListener(arg);
            removeListeners(args...);
        }

        void removeListeners() {}

        void executeAll(Args... args) {
            CPPUTILS_LISTENERS_SET_DEBUG_INIT

            if (std::is_same<Mutex, DummyMutex>::value) {
                auto end = listeners.end();
                for (auto iter = listeners.begin(); iter != end;) {
                    if (iter->second(args...) == DELETE_LISTENER) {
                        iter = listeners.erase(iter);
                    } else {
                        ++iter;
                    }
                }
            } else {
                std::vector<std::pair<int, Listener>> temp;
                {
                    std::lock_guard<Mutex> _(mutex);
                    temp.assign(listeners.begin(), listeners.end());
                };

                std::vector<int> scheduledForDelete;
                for (const auto& pair : temp) {
                    if (pair.second(args...) == DELETE_LISTENER) {
                        scheduledForDelete.push_back(pair.first);
                    }
                }

                std::lock_guard<Mutex> _(mutex);
                for (int key : scheduledForDelete) {
                    listeners.erase(key);
                }
            }
        }

        void operator()(Args... args) {
            executeAll(args...);
        }

        bool hasListenersToExecute() const {
            CPPUTILS_LISTENERS_SET_DEBUG_INIT
            std::lock_guard<Mutex> _(mutex);
            return !listeners.empty();
        }

        void clear() {
            CPPUTILS_LISTENERS_SET_DEBUG_INIT
            std::lock_guard<Mutex> _(mutex);
            listeners.clear();
        }
    };

    template <typename... Args>
    using ListenersSet = BaseListenersSet<DummyMutex, Args...>;

    template <typename... Args>
    using SynchronizedListenersSet = BaseListenersSet<std::mutex, Args...>;
}

#define CPPUTILS_DEFINE_LISNERS_SET()


#endif //VOCALTRAINER_LISTENERSSET_H
