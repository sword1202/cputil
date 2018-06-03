//
// Created by Semyon Tikhonenko on 6/3/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef ConcurrentModificationAssertBegin

#include <assert.h>

#define ConcurrentModificationAssertBegin(variable) decltype(variable) ConcurrentModificationAssertBegin_##variable = variable
#define ConcurrentModificationAssertEnd(variable) assert(ConcurrentModificationAssertBegin_##variable == variable);

#endif
