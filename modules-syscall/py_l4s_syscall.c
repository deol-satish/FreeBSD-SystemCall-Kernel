#include <Python.h>
#include <malloc.h>
#include <sys/syscall.h>

#include "py_l4s_syscall.h"

static PyObject *method_l4s_drl_update_cwnd(PyObject *self, PyObject *args) {
    u_int prob, check;

    /* Parse arguments */
    if(!PyArg_ParseTuple(args, "III", &prob, &check)) {
        PyErr_SetString(PyExc_Exception, "Error parsing arguments.");
        return NULL;
    }

    int err = syscall(588, prob);
    return PyLong_FromLong(err);
}


static PyObject *method_l4s_drl_get_buffer(PyObject *self, PyObject *args) {
    struct data buffer;
    int size = sizeof(buffer);

    int err = syscall(589, &buffer, &size);
    if (err < 0) {
        PyErr_SetString(PyExc_Exception, "Error during system call.");
        return NULL;
    }

    PyObject *item = PyList_New(0);
    PyList_Append(item, PyLong_FromLong(buffer[i].cwnd));
	PyList_Append(item, PyLong_FromLong(buffer[i].smoothed_rtt));
    PyList_Append(item, PyLong_FromLong(buffer[i].cong_events));
    PyList_Append(item, PyLong_FromLong(buffer[i].laddr));
    PyList_Append(item, PyLong_FromLong(buffer[i].lport));


    free(buffer);

    return item;
}


static PyMethodDef PyMethods_syscalls[] = {
    {"l4s_drl_update_cwnd", method_l4s_drl_update_cwnd, METH_VARARGS, "Python wrapper for l4s_drl_update_cwnd system call"},
    {"l4s_drl_get_buffer", method_l4s_drl_get_buffer, METH_VARARGS, "Python wrapper for l4s_drl_get_buffer system call"},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef PyModule_syscalls = {
    PyModuleDef_HEAD_INIT,
    "syscalls",
    "Python wrapper for FreeBSD13.1 MPTCP ystem calls.",
    -1,
    PyMethods_syscalls
};

PyMODINIT_FUNC PyInit_syscalls(void) {
    return PyModule_Create(&PyModule_syscalls);
}