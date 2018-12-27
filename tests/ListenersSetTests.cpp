//
// Created by Semyon Tikhonenko on 2018-12-27.
//

#include "catch.hpp"
#include "../ListenersSet.h"
#include "../Primitives.h"

using namespace CppUtils;

#define ListenersSet CppUtils::ListenersSet
#define TOKEN std::string("ListenersSet")
#define FuncObj1 FuncObj1
#include "ListenersSetTests.h"

#define ListenersSet CppUtils::SynchronizedListenersSet
#define TOKEN std::string("SynchronizedListenersSet")
#define FuncObj1 FuncObj2
#include "ListenersSetTests.h"
