//
// Created by Semyon Tikhonenko on 11/10/17.
//

#ifndef PYTHONALGORITHMANDROID_PYTHONUTILS_H
#define PYTHONALGORITHMANDROID_PYTHONUTILS_H

#include <Python.h>
#include "../config.h"

namespace CppUtils {
    namespace PythonUtils {
        CPP_UTILS_DLLHIDE PyObject* CreatePythonListFromDoubleArray(double* array, int size);
    }
}

#endif //PYTHONALGORITHMANDROID_PYTHONUTILS_H
