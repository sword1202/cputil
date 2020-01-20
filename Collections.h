//
// Created by Semyon Tykhonenko on 1/20/20.
// Copyright (c) 2020 Semyon Tikhonenko. All rights reserved.
//

#ifndef VOCALTRAINER_COLLECTIONS_H
#define VOCALTRAINER_COLLECTIONS_H


namespace CppUtils {
    namespace Collections {
        template <typename T>
        const std::vector<T>& emptyVector() {
            static std::vector<T> vector;
            return vector;
        }
    }
};


#endif //VOCALTRAINER_COLLECTIONS_H
