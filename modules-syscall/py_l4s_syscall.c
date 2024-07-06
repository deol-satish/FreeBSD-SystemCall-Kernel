#include <Python.h>
#include <malloc.h>
#include <sys/syscall.h>

#include "py_l4s_syscall.h"

static PyObject *method_l4s_drl_update_prob(PyObject *self, PyObject *args) {
    u_int prob, check;

    /* Parse arguments */
    if(!PyArg_ParseTuple(args, "II", &prob, &check)) {
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
    PyList_Append(item, PyLong_FromLong(buffer.flows_cnt));
	PyList_Append(item, PyLong_FromLong(buffer.limit));
    PyList_Append(item, PyLong_FromLong(buffer.quantum));
    PyList_Append(item, PyLong_FromLong(buffer.tot_pkts));
    PyList_Append(item, PyLong_FromLong(buffer.tot_bytes));
    PyList_Append(item, PyLong_FromLong(buffer.length));
	PyList_Append(item, PyLong_FromLong(buffer.len_bytes));
    PyList_Append(item, PyLong_FromLong(buffer.drops));
    PyList_Append(item, PyLong_FromLong(buffer.max_ecnth));
    PyList_Append(item, PyLong_FromLong(buffer.alpha));
    PyList_Append(item, PyLong_FromLong(buffer.beta));
	PyList_Append(item, PyLong_FromLong(buffer.burst_allowance));
    PyList_Append(item, PyLong_FromLong(buffer.current_qdelay));
    PyList_Append(item, PyLong_FromLong(buffer.qdelay_old));
    PyList_Append(item, PyLong_FromLong(buffer.avg_dq_time));
    PyList_Append(item, PyLong_FromLong(buffer.dq_count));

    return item;
}


static PyMethodDef PyMethods_syscalls[] = {
    {"l4s_drl_update_prob", method_l4s_drl_update_prob, METH_VARARGS, "Python wrapper for l4s_drl_update_prob system call"},
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