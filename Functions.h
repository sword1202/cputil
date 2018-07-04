//
// Created by Semyon Tikhonenko on 6/12/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_FUNCTIONS_H
#define VOCALTRAINER_FUNCTIONS_H

#include <functional>
#include <deque>

namespace CppUtils {
    namespace Functions {
        template<typename FuncCollection>
        void ExecuteAll(const FuncCollection &collection) {
            for (const auto &func : collection) {
                func();
            }
        }

        template<typename FuncCollection>
        void ExecuteAllAndClear(FuncCollection &collection) {
            ExecuteAll(collection);
            collection.clear();
        }

        template<typename Func>
        class BasicInitQueue : public std::deque<Func> {
            void **initialisationIndicatorObject;
        public:
            template<typename T>
            BasicInitQueue(T **initialisationIndicatorObject) :
                    initialisationIndicatorObject((void**)initialisationIndicatorObject) {
            }

            template<typename F>
            void executeWhenInitialised(const F &func) {
                if (*initialisationIndicatorObject) {
                    func();
                } else {
                    std::deque<Func>::push_back(func);
                }
            }

            void executeAll() {
                ExecuteAllAndClear(*this);
            }
        };

        typedef BasicInitQueue<std::function<void()>> InitQueue;
    };
}


#endif //VOCALTRAINER_FUNCTIONS_H
