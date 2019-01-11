//
// Created by Semyon Tikhonenko on 2019-01-11.
//

#ifndef MVXGENERATOR_DUMMYMUTEX_H
#define MVXGENERATOR_DUMMYMUTEX_H

namespace CppUtils {
    struct DummyMutex {
        inline void lock() {}
        inline void unlock() {}
    };
}


#endif //MVXGENERATOR_DUMMYMUTEX_H
