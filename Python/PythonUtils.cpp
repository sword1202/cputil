
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

        std::vector<double> CreateVectorFromDoublePythonList(PyObject* list) {
            int size = PyList_Size(list);
            std::vector<double> result(size);
            for (int i = 0; i < size; i++) {
                PyObject *item = PyList_GetItem(list, i);
                if(!PyFloat_Check(item)) {
                    PyErr_SetString(PyExc_TypeError, "list items must be doubles.");
                    return std::vector<double>();
                }

                result[i] = PyFloat_AsDouble(item);
            }

            return result;
        }
    }
}