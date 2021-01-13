// include the utils header containing code for encode and decode operations
#include "rle_utils.h"
// include the docs header for docstrings for package
#include "rle_docs.h"

PyObject* encode_c(PyObject* self, PyObject* args)
{
    // Create a Python object to hold the iterable to be processed
    PyObject* iterable = NULL;

    // Parse the input arguments to get the input parameters
    if( !PyArg_ParseTuple(args, "O", &iterable) )
        return Py_None;

    // check if the iterable has zero length,
    if( PySequence_Length(iterable) == 0 )
        PyErr_SetString( PyExc_AssertionError, "Sequence passed has zero length");

    // if the length of sequence is returned -1
    else if( PySequence_Length(iterable) == -1 )
        PyErr_SetString(PyExc_ValueError, "The given object is not iterable.");

    // create a code structure to hold the encoded result
    struct code result;

    // get the run length encoding of the iterable
    result = encode_sequence(iterable);

    // return value and count list as object back to the caller
    return Py_BuildValue("OO", result.values, result.counts);
}


PyObject* decode_c(PyObject* self, PyObject* args)
{
    // create a python object to hold the values
    PyObject* values = NULL;
    // create a python object to hold the counts
    PyObject* counts = NULL;

    // Parse the input arguments to get the input parameters
    if( !PyArg_ParseTuple(args, "OO", &values, &counts) )
        return Py_None;

    // check if the value argument is iterable
    if( PySequence_Length(values) == -1 )
        PyErr_SetString(PyExc_ValueError, "values argument is not iterable.");

    // check if the count argument is iterable
    else if( PySequence_Length(counts) == -1)
        PyErr_SetString(PyExc_ValueError, "counts argument is not iterable.");

    // check if the length of value list is same as that if count list
    else if( PySequence_Length(values) != PySequence_Length(counts) )
        PyErr_SetString(PyExc_AssertionError, "len(values) != len(counts)");

    PyObject* decoded_list = decode_sequence(values, counts);

    // return value and count list as object back to the caller
    return Py_BuildValue("O", decoded_list);
}
//########        MODULE LEVEL FUNCTIONS        ########

// method definitions
static PyMethodDef methods[] = {
  { "encode", encode_c, METH_VARARGS, encode_doc},
  { "decode", decode_c, METH_VARARGS, decode_doc},
  { NULL, NULL, 0, NULL }
};

// module definition
static struct PyModuleDef rle_fast = {
    PyModuleDef_HEAD_INIT,
    "rle_fast",
    rle_module_doc,
    -1,
    methods
};

// create the module
PyMODINIT_FUNC PyInit_rle_fast(void) {
    Py_Initialize();
    return PyModule_Create(&rle_fast);
}
