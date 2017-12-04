
#include <Python.h>
#include "PythonUtils.h"

namespace CppUtils {
    namespace PythonUtils {
        PyObject* CreatePythonListFromDoubleArray(double* array, int size)
        {
            assert(size >= 0);
            PyObject *list = PyList_New(size);

            for (int i = 0; i < size; ++i) {
                PyList_SetItem(list, i, PyFloat_FromDouble(array[i]));
            }

            return list;
        }

        PyObject* CreatePythonComplexList(double* real, double* image, int size)
        {
            assert(size >= 0);
            PyObject *list = PyList_New(size);

            for (int i = 0; i < size; ++i) {
                Py_complex complex;
                complex.imag = image[i];
                complex.real = real[i];
                PyList_SetItem(list, i, PyComplex_FromCComplex(complex));
            }

            return list;
        }

        std::vector<double> CreateVectorFromDoublePythonList(PyObject* list) {
            int size = PyList_Size(list);
            std::vector<double> result(size);
            for (int i = 0; i < size; i++) {
                PyObject *item = PyList_GetItem(list, i);
                result[i] = PyFloat_AsDouble(item);
            }

            PyObject *error = PyErr_Occurred();
            if (error) {
                PyErr_SetFromErrno(error);
            }

            return result;
        }
    }
}