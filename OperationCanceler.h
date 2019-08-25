//
// Created by Semyon Tikhonenko on 2018-12-28.
//

#ifndef VOCALTRAINER_OPERATIONCANCELER_H
#define VOCALTRAINER_OPERATIONCANCELER_H

#include <atomic>
#include <memory>

namespace CppUtils {
    class OperationCanceler {
        std::atomic_bool cancelled;
        OperationCanceler();
    public:
        bool isCancelled() const;
        void cancel();

        static std::shared_ptr<OperationCanceler> create();
    };

    typedef std::shared_ptr<OperationCanceler> OperationCancelerPtr;
}

#endif //VOCALTRAINER_OPERATIONCANCELER_H
