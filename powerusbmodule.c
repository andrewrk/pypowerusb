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

    if (success < 0) {
        PyErr_SetString(PowerUsbError, "Unable to initialize.");
        return NULL;
    }
    Py_RETURN_NONE;
}

static PyObject * powerusb_check_status(PyObject * self, PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    int powerusb_count = CheckStatusPowereUSB();

    if (powerusb_count < 0) {
        PyErr_SetString(PowerUsbError, "Unable to .");
        return NULL;
    }
    
    return PyLong_FromLong(powerusb_count);
}


static PyObject * powerusb_terminate(PyObject * self, PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    int success = ClosePowerUSB();

    if (success < 0) {
        PyErr_SetString(PowerUsbError, "Unable to close device.");
        return NULL;
    }
    Py_RETURN_NONE;
}

static PyObject * powerusb_set_current_device(PyObject * self, PyObject * args)
{
    int device_number;
    
    if (!PyArg_ParseTuple(args, "i", &device_number))
        return NULL;

    int success = SetCurrentPowerUSB(device_number);

    if (success < 0) {
        PyErr_SetString(PowerUsbError, "Unable to set current device.");
        return NULL;
    }
    Py_RETURN_NONE;
}

static PyObject * powerusb_set_state(PyObject * self, PyObject * args)
{
    char port1_on, port2_on;
    
    if (!PyArg_ParseTuple(args, "bb", &port1_on, &port2_on))
        return NULL;

    int p1 = port1_on ? 1 : 0;
    int p2 = port2_on ? 1 : 0;

    int success = SetPortPowerUSB(p1, p2);

    if (success < 0) {
        PyErr_SetString(PowerUsbError, "Unable to set power state.");
        return NULL;
    }
    Py_RETURN_NONE;
}

static PyObject * powerusb_set_default_state(PyObject * self, PyObject * args)
{
    char port1_on, port2_on;
    
    if (!PyArg_ParseTuple(args, "bb", &port1_on, &port2_on))
        return NULL;

    int p1 = port1_on ? 1 : 0;
    int p2 = port2_on ? 1 : 0;

    int success = SetDefaultStatePowerUSB(p1, p2);

    if (success < 0) {
        PyErr_SetString(PowerUsbError, "Unable to set default state.");
        return NULL;
    }
    Py_RETURN_NONE;
}

static PyObject * powerusb_state(PyObject * self, PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    int p1, p2;
    int success = ReadPortState(&p1, &p2);

    if (success < 0) {
        PyErr_SetString(PowerUsbError, "Unable to read port state.");
        return NULL;
    }

    char p1bool = p1 ? 1 : 0;
    char p2bool = p2 ? 1 : 0;

    return Py_BuildValue("(bb)", p1bool, p2bool);
}

static PyObject * powerusb_default_state(PyObject * self, PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    int p1, p2;
    int success = ReadDefaultPortState(&p1, &p2);

    if (success < 0) {
        PyErr_SetString(PowerUsbError, "Unable to read default port state.");
        return NULL;
    }

    char p1bool = p1 ? 1 : 0;
    char p2bool = p2 ? 1 : 0;

    return Py_BuildValue("(bb)", p1bool, p2bool);
}
static PyObject * powerusb_firmware_version(PyObject * self, PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    int version = GetFirmwareVersion();

    if (version < 0) {
        PyErr_SetString(PowerUsbError, "Unable to get firmware version.");
        return NULL;
    }
    return PyLong_FromLong(version);
}

static PyObject * powerusb_start_watchdog(PyObject * self, PyObject * args)
{
    int hb_time, hb_miss_count, reset_time;
    
    if (!PyArg_ParseTuple(args, "iii", &hb_time, &hb_miss_count, &reset_time))
        return NULL;

    int success = StartWatchdogTimer(hb_time, hb_miss_count, reset_time);

    if (success < 0) {
        PyErr_SetString(PowerUsbError, "Unable to start watchdog timer.");
        return NULL;
    }
    Py_RETURN_NONE;
}

static PyObject * powerusb_stop_watchdog(PyObject * self, PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    int success = StopWatchdogTimer();

    if (success < 0) {
        PyErr_SetString(PowerUsbError, "Unable to stop watchdog timer.");
        return NULL;
    }
    Py_RETURN_NONE;
}

static PyObject * powerusb_watchdog_status(PyObject * self, PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    int status = GetWatchdogStatus();

    if (status < 0) {
        PyErr_SetString(PowerUsbError, "Unable to get watchdog status.");
        return NULL;
    }
    
    return PyLong_FromLong(status);
}

static PyObject * powerusb_send_heartbeat(PyObject * self, PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    int success = SendHeartBeat();

    if (success < 0) {
        PyErr_SetString(PowerUsbError, "Unable to send heartbeat.");
        return NULL;
    }
    Py_RETURN_NONE;
}

static PyObject * powerusb_cycle_power(PyObject * self, PyObject * args)
{
    int reset_time;
    
    if (!PyArg_ParseTuple(args, "i", &reset_time))
        return NULL;

    int success = PowerCycle(reset_time);

    if (success < 0) {
        PyErr_SetString(PowerUsbError, "Unable to cycle power.");
        return NULL;
    }
    Py_RETURN_NONE;
}


/* List of functions defined in the module */
static PyMethodDef powerusbMethods[] = {
    {"initialize", powerusb_initialize, METH_VARARGS, "initialize()\n"
        "Initializes the Power USB API. No other functions can be called till "
        "the API is initialized."},
    {"check_status", powerusb_check_status, METH_VARARGS, "powerusb_count_int = check_status()\n"
        "Checks to see if the power USB is connected to the computer. Returns "
        "the number of Power USBs connected."},
    {"terminate", powerusb_terminate, METH_VARARGS, "terminate()\n"
        "Closes the PowerUSB API. Should be called in application exit "
        "function such as OnDestroy."},
    {"set_current_device", powerusb_set_current_device, METH_VARARGS, "set_current_device(device_number_int)\n"
        "Changes the current PowerUSB. By default the first connected PowerUSB "
        "is active. If multiple PowerUSBs are connected, you can use this "
        "function to change the current PowerUSB. Once this function is "
        "called, the method set_state will be directed to the "
        "selected PowerUSB. Maximum of 4 powerUSBs are currently supported."},
    {"set_state", powerusb_set_state, METH_VARARGS, "set_state(port1_bool, port2_bool)\n"
        "Sets the power on/off state of the two outlets."},
    {"set_default_state", powerusb_set_default_state, METH_VARARGS, "set_default_state(port1_bool, port2_bool)\n"
        "Sets the default power up state of the Power USB (when connected to "
        "Computer). If set to 1, the outlet will come on when the attached "
        "computer is booted up.\n"
        "set_default_state(port1_boolean, port2_boolean)"},
    {"state", powerusb_state, METH_VARARGS, "port1_bool, port2_bool = state()\n"
        "Returns a tuple of the on/off state of the 2 outlets."},
    {"default_state", powerusb_default_state, METH_VARARGS, "port1_bool, port2_bool = default_state()\n"
        "Returns a tuple of the default on/off state of the outlets. The "
        "outlets go into this state when PowerUSB is powered on."},
    {"firmware_version", powerusb_firmware_version, METH_VARARGS, "version_int = firmware_version()\n"
        "Returns the firmware version of the PowerUSB.\n\n"
        "Version 1:\n"
        " - basic power control functions\n\n"
        "Version 2:\n"
        " - read the outlet states\n"
        " - watchdog functions"},
    {"start_watchdog", powerusb_start_watchdog, METH_VARARGS, "start_watchdog(hb_time, hb_miss_count, reset_time)\n"
        "Starts a "
        "watchdog in the PowerUSB. The PowerUSB starts a monitoring thread and "
        "expects a heartbeat from this moment. If the attached computer misses "
        "the heartbeat for certain number of times (probably due to hangup), "
        "it switches off the outlet 1 for a certain duration and switches it "
        "on to do a PowerCycle. After the PowerCycle, the watchdog timer is "
        "stopped. The watchdog timer has to be restarted by the attached "
        "computer after the reboot.\n"
        "hb_time: This is the time within which the PowerUSB expects a heartbeat.\n"
        "hb_miss_count: If this many heartbeats are missed, the PowerUSB "
            "starts the power cycle to reboot.\n"
        "reset_time: The amount of time to swich off the outlet during the power cycle.\n"},
    {"stop_watchdog", powerusb_stop_watchdog, METH_VARARGS, "stop_watchdog()\n"
        "Stops the watchdog timer. The PowerUSB ignores any received heartbets "
        "and will not monitor the attached computer."},
    {"watchdog_status", powerusb_watchdog_status, METH_VARARGS, "status_int = watchdog_status()\n"
        "Returns the current mode of the Watchdog.\n"
        "0: Watchdog is not active\n"
        "1: Watchdog is active\n"
        "2: PowerCycle"},
    {"send_heartbeat", powerusb_send_heartbeat, METH_VARARGS, "send_heartbeat()\n"
        "Send a heartbeat message to PowerUSB."},
    {"cycle_power", powerusb_cycle_power, METH_VARARGS, "cycle_power(reset_time)\n"
        "Switches the outlet off for a specified duration and then back on"
        "to reboot the attached computer.\n"},
    {NULL, NULL, 0, NULL}       // sentinel
};

static PyModuleDef powerusbModule = {
    PyModuleDef_HEAD_INIT,
    "powerusb",                                      // name of module
    "Python library to control PowerUSB.\n"
        "any method can raise a powerusb.error exception.", // module documentation
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
