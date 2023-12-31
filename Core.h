//
// Created by Semyon Tikhonenko on 8/26/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_CORE_H
#define VOCALTRAINER_CORE_H


namespace CppUtils {
    template <typename Func>
    class ExecuteInTheEndOfScope {
        Func func;
    public:
        explicit ExecuteInTheEndOfScope(const Func& func) : func(func) {
        }

        ~ExecuteInTheEndOfScope() {
            func();
        }
    };
};


#endif //VOCALTRAINER_CORE_H
