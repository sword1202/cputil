
#include <Python.h>

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
    }
}