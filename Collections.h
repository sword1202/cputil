//
// Created by Semyon Tykhonenko on 1/20/20.
// Copyright (c) 2020 Semyon Tikhonenko. All rights reserved.
//

#ifndef VOCALTRAINER_COLLECTIONS_H
#define VOCALTRAINER_COLLECTIONS_H

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

namespace CppUtils {
    namespace Collections {
        template <typename T>
        const std::vector<T>& emptyVector() {
            static std::vector<T> vector;
            return vector;
        }

#ifdef __OBJC__
        template <typename Container>
        NSMutableArray<NSNumber*>* ToPrimitivesNSArray(const Container& container) {
            NSMutableArray* result = [NSMutableArray arrayWithCapacity:static_cast<NSUInteger>(container.size())];
            for (auto sample : container) {
                [result addObject:@(sample)];
            }

            return result;
        }
#endif
    }
};


#endif //VOCALTRAINER_COLLECTIONS_H
