//
// Created by Semyon Tikhonenko on 2018-12-28.
//

#include "OperationCanceler.h"

bool OperationCanceler::isCancelled() const {
    return cancelled;
}

void OperationCanceler::cancel() {
    cancelled = true;
}

std::shared_ptr<OperationCanceler> OperationCanceler::create() {
    return std::shared_ptr<OperationCanceler>(new OperationCanceler());
}

OperationCanceler::OperationCanceler() {
    cancelled = false;
}
