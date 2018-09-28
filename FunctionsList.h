//
// Created by Semyon Tikhonenko on 9/28/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_FUNCTIONSLIST_H
#define VOCALTRAINER_FUNCTIONSLIST_H

#include <vector>
#include <functional>
#include "Functions.h"

namespace CppUtils {
    template<typename... Args>
    class FunctionsList : public std::vector<std::function<void(Args...)>> {
    public:
        void operator()(Args... args) {
            Functions::ExecuteAll(*this, args...);
        }
    };
}


#endif //VOCALTRAINER_FUNCTIONSLIST_H
