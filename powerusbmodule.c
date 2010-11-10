#include <Python.h>

#include "PwrUSBInc.h"

#ifdef __cplusplus
extern "C" {
#endif

static PyObject * PowerUsbError;

#define PowerUsbObject_Check(v) ((v)->ob_type == &PowerUsb_Type)

/* Function of no arguments returning new PowerUsb object */
static PyObject * powerusb_initialize(PyObject * self, PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    int success;
    int mode;
    success = InitPowerUSB(&mode);

    // I don't know what mode means.

    if (success >= 0)
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}

static PyObject * powerusb_terminate(PyObject * self, PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    int success = ClosePowerUSB();

    if (success >= 0)
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}

static PyObject * powerusb_set_state(PyObject * self, PyObject * args)
{
    char port1_on, port2_on;
    
    if (!PyArg_ParseTuple(args, "bb", &port1_on, &port2_on))
        return NULL;

    int p1 = port1_on ? 1 : 0;
    int p2 = port2_on ? 1 : 0;

    int success = SetPortPowerUSB(p1, p2);

    if (success >= 0)
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}

/* List of functions defined in the module */
static PyMethodDef powerusbMethods[] = {
    {"initialize", powerusb_initialize, METH_VARARGS, "must be called before anything else"},
    {"set_state", powerusb_set_state, METH_VARARGS, "change whether each port is on or off"},
    {"terminate", powerusb_terminate, METH_VARARGS, "must be called after everything else"},
    {NULL, NULL, 0, NULL}       // sentinel
};

static PyModuleDef powerusbModule = {
    PyModuleDef_HEAD_INIT,
    "powerusb",                                      // name of module
    "Python library to control PowerUSB", // module documentation
    // size of per-interpreter state of the module, or -1 if
    // the module keeps state in global variables.
    -1,
    powerusbMethods
};

// initialization function for the module.
// the name that gets exported here matters.
PyMODINIT_FUNC
PyInit_powerusb()
{
    PyObject * m;

    m = PyModule_Create(&powerusbModule);
    if (m == NULL)
        return NULL;

    // create the custom error
    PowerUsbError = PyErr_NewException("PowerUsb.error", NULL, NULL);
    Py_INCREF(PowerUsbError);
    PyModule_AddObject(m, "error", PowerUsbError);

    return m;
}

#ifdef __cplusplus
}
#endif
