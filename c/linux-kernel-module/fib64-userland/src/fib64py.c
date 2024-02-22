/* Note: Python.h must be included before any other system headers */
#include <Python.h>
#include <stdio.h>
#include "fib64/userops.h"

#define FIB64_PYMODULE "fib64py"
#define FIB64READER_PTR(p) ((Fib64Reader *)(p))

#ifndef FIB64_BUFSIZE
# define FIB64_BUFSIZE 32
#endif

#define FIB64_ERROR_BUFSIZE 255
#define FIB64_NOCONTEXT_MSG \
	"Fib64Reader can only be used inside a context manager "\
	"(e.g., `with Fib64Reader() as fib64:`)"
#define TOKEN_TO_STR(t) #t
#define STRINGIFY(t) TOKEN_TO_STR(t)
#define PY_FQTYPE(m, t) m "." STRINGIFY(t)

static char FIB64_ERROR_BUF[FIB64_ERROR_BUFSIZE + 1] = { '\0' };

typedef struct {
	PyObject_HEAD
	uint64_t buf[FIB64_BUFSIZE];
	int buf_count;
	unsigned int pos : 31;
	unsigned int in_context : 1;
} Fib64Reader;

static int
Fib64Reader_init(PyObject *self, PyObject *args, PyObject *kwargs);

static PyObject *
Fib64Reader_enter(PyObject *self);

static PyObject *
Fib64Reader_exit(PyObject *self, PyObject *args);

static PyObject *
Fib64Reader_iter(PyObject *self);

static PyObject *
Fib64Reader_next(PyObject *self);

static void
fib64_error(PyObject *exc_type, int sys_errno);

static PyMethodDef Fib64Reader_methods[] = {
	{
		.ml_name = "__enter__",
		.ml_meth = (PyCFunction)Fib64Reader_enter,
		.ml_flags = METH_NOARGS,
		.ml_doc = "Enter " STRINGIFY(Fib64Reader) " context"
	},
	{
		.ml_name = "__exit__",
		.ml_meth = (PyCFunction)Fib64Reader_exit,
		.ml_flags = METH_VARARGS,
		.ml_doc = "Exit " STRINGIFY(Fib64Reader) " context"
	},
	{NULL, NULL, 0, NULL} /* sentinel */
};

static PyTypeObject Fib64ReaderType = {
	PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = PY_FQTYPE(FIB64_PYMODULE, Fib64Reader),
	.tp_doc = "",
	.tp_basicsize = sizeof(Fib64Reader),
	.tp_itemsize = 0,
	.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_new = PyType_GenericNew,
	.tp_init = Fib64Reader_init,
	.tp_dealloc = (destructor)PyObject_Del,
	.tp_iter = Fib64Reader_iter,
	.tp_iternext = Fib64Reader_next,
	.tp_methods = Fib64Reader_methods
};

static struct PyModuleDef fib64py = {
	PyModuleDef_HEAD_INIT,
	.m_name = FIB64_PYMODULE,
	.m_doc = "",
	.m_size = -1
};

PyMODINIT_FUNC PyInit_fib64py(void)
{
	PyObject *m = NULL;

	if (PyType_Ready(&Fib64ReaderType) < 0)
		return NULL;

	m = PyModule_Create(&fib64py);

	if (!m)
		return NULL;

	Py_INCREF(&Fib64ReaderType);
	PyModule_AddObject(m, "Fib64Reader", (PyObject *)&Fib64ReaderType);
	return m;
}

static int
Fib64Reader_init(PyObject *self, PyObject *args, PyObject *kwargs)
{
	FIB64READER_PTR(self)->in_context = 0;
	FIB64READER_PTR(self)->buf_count = 0;
	FIB64READER_PTR(self)->pos = 0;
	return 0;
}

static PyObject *
Fib64Reader_enter(PyObject *self)
{
	if (fib64_open() == FIB64_ERROR) {
		fib64_error(PyExc_OSError, fib64_errno());
		return NULL;
	}

	FIB64READER_PTR(self)->in_context = 1;
	return self;
}

static PyObject *
Fib64Reader_exit(PyObject *self, PyObject *args)
{
	if (fib64_close() == FIB64_ERROR) {
		fib64_error(PyExc_OSError, fib64_errno());
		Py_RETURN_FALSE;
	}

	FIB64READER_PTR(self)->in_context = 0;
	Py_RETURN_FALSE;
}

static PyObject *
Fib64Reader_iter(PyObject *self)
{
	if (!FIB64READER_PTR(self)->in_context) {
		PyErr_SetString(PyExc_NotImplementedError, FIB64_NOCONTEXT_MSG);
		return NULL;
	}

	Py_INCREF(self);
	return self;
}

static PyObject *
Fib64Reader_next(PyObject *self)
{
	PyObject *result = NULL;
	int vals_read;

	Py_INCREF(self);

	if (!FIB64READER_PTR(self)->in_context) {
		PyErr_SetString(PyExc_NotImplementedError, FIB64_NOCONTEXT_MSG);
		return NULL;
	}

	if (!FIB64READER_PTR(self)->pos) {
		FIB64READER_PTR(self)->buf_count = 0;
		vals_read = fib64_readvals(FIB64READER_PTR(self)->buf, FIB64_BUFSIZE);

		if (vals_read == FIB64_ERROR) {
			fib64_error(PyExc_OSError, fib64_errno());
			return NULL;
		}

		FIB64READER_PTR(self)->buf_count = (unsigned int)vals_read;
	}

	if (FIB64READER_PTR(self)->pos >= FIB64READER_PTR(self)->buf_count) {
		PyErr_SetNone(PyExc_StopIteration);
		return NULL;
	}

	result = PyLong_FromUnsignedLong(FIB64READER_PTR(self)->buf[FIB64READER_PTR(self)->pos]);

	if (!result) {
		PyErr_SetString(PyExc_RuntimeError, "Failed to create Python `int`");
		return NULL;
	}

	FIB64READER_PTR(self)->pos = (FIB64READER_PTR(self)->pos + 1) % FIB64_BUFSIZE;
	Py_DECREF(self);
	return result;
}

static void
fib64_error(PyObject *exc_type, int sys_errno)
{
	snprintf(FIB64_ERROR_BUF, FIB64_ERROR_BUFSIZE,
		 "%s: %s", STRINGIFY(Fib64Reader), strerror(sys_errno));

	PyErr_SetString(exc_type, FIB64_ERROR_BUF);
}
