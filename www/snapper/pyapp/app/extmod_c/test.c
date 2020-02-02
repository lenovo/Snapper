/*---------------------------------------------------------------------------
//  Copyright (c) 2018-present, Lenovo. All rights reserved.
//  Licensed under BSD, see COPYING.BSD file for details.
//---------------------------------------------------------------------------
*/

#include <Python.h>


#undef IS_PY3K
#if PY_MAJOR_VERSION >= 3
#define IS_PY3K
#endif


/*
*/
static PyObject* Snapper_Test(PyObject* self, PyObject *args)
{

    return Py_BuildValue("{s:i,s:i}","return", 0, "test",1);
}


///////////////////////////////////////
static PyMethodDef test_funcs[] = {
    {"Snapper_Test", (PyCFunction)Snapper_Test, METH_VARARGS, "Snapper_Test(): test c module\n"},
    {NULL, NULL, 0, NULL}
};

#ifdef IS_PY3K
static struct PyModuleDef testmodule = {
   PyModuleDef_HEAD_INIT,
   "_test",     /* name of module */
   NULL,       /* module documentation, may be NULL */
   -1,         /* size of per-interpreter state of the module,
                  or -1 if the module keeps state in global variables. */
   test_funcs
};
PyMODINIT_FUNC PyInit__test(void)
{
    return PyModule_Create(&testmodule);
}

#else
void init_test(void)
{
    Py_InitModule("_test", test_funcs);
}
#endif
