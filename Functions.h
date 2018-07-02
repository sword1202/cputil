//
// Created by Semyon Tikhonenko on 6/12/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_FUNCTIONS_H
#define VOCALTRAINER_FUNCTIONS_H


namespace Functions {
    template<typename FuncCollection>
    void executeAll(const FuncCollection& collection) {
        for (const auto& func : collection) {
            func();
        }
    }

    template<typename FuncCollection>
    void executeAllAndClear(FuncCollection& collection) {
        executeAll(collection);
        collection.clear();
    }
};


#endif //VOCALTRAINER_FUNCTIONS_H
