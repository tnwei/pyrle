#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdbool.h>

// create a structure to hold the encoded result
struct code
{
    // python list object containing the values in encoded result
    PyObject* values;
    // python list object containing the counts to values in encoded result
    PyObject* counts;
};

struct code encode_sequence( PyObject* sequence )
{
    // create an iterator object to the sequence
    PyObject* iterator = PyObject_GetIter(sequence);
    // create a python object to hold the current item from the sequence
    PyObject* current_item;

    // create a new empty python list object to hold all values in sequence
    PyObject* values_list = PyList_New(0);
    // create a new empty python list object to hold counts of values in value list
    PyObject* count_list = PyList_New(0);

    // get first item from sequence and store it in variable for further use
    long int current_run_value = PyLong_AsLong( PyIter_Next(iterator) );
    // create variable to hold the run length of current item
    Py_ssize_t current_run_length = 1;

    // insert the current_run_value in value list
    PyList_Append(values_list, PyLong_FromLong(current_run_value) );

    // repeat the following as long as some element is returned from sequence
    while( (current_item = PyIter_Next(iterator) ) )
    {
        long int current_item_value = PyLong_AsLong(current_item);

        // if the current element is still part of the lenght,
        if ( current_item_value == current_run_value )
            // increment to count of current element
            ++current_run_length;
        // otherwise,
        else
        {
            // add count of current run to the count list
            PyList_Append(count_list, PyLong_FromSsize_t(current_run_length) );

            // add the current element to value list
            PyList_Append(values_list, current_item);

            // update the current run length for current element
            current_run_length = 1;

            current_run_value = current_item_value;
        }
    }

    // now process the last count
    PyList_Append(count_list, PyLong_FromSsize_t(current_run_length) );

    // remove the current reference to the iterator
    Py_DECREF(iterator);

    // create a structure to hold the value and count lists.
    // this is because, C does not support returning multiple values from functions
    // so we will wrap these lists in a structure, and return the structure
    struct code encoded;

    // add the value list to the structure
    encoded.values = values_list;

    // add the count list to the structure
    encoded.counts = count_list;

    if (PyErr_Occurred())
    {
        // if an error is thrown at some point in the code,
        // most likely, the user is comparing strings.
        // this is because, we are assuming the user only uses sequences with numbers,
        // so when a string is passed, the function PyLong_AsLong throws an error.
        // because, characters and strings cant be interpreted as long objects
        PyErr_SetString(PyExc_NotImplementedError, "Encoding of strings is not currently supported.");
    }

    // return this structure
    return encoded;
}

PyObject* decode_sequence(PyObject* values, PyObject* counts)
{
    // create a empty python list object to hold the calculated sequence
    PyObject* decoded_list = PyList_New(0);

    // create an iterator object for the value list
    PyObject* value_iterator = PyObject_GetIter( values );
    // create a python object to hold the current item from the sequence
    PyObject* current_value;

    // create an iterator object for the value list
    PyObject* count_iterator = PyObject_GetIter( counts );
    // create a python object to hold the current item from the sequence
    PyObject* current_count;

    // keep repeating until you can get the next value from value list
    while( ( current_value = PyIter_Next(value_iterator) ) )
    {
        // get the count of current value from count list
        current_count = PyIter_Next( count_iterator);

        Py_ssize_t current_count_as_integer = PyLong_AsSsize_t(current_count);

        for( Py_ssize_t i = 0; i < current_count_as_integer; ++i )
        {
            PyList_Append(decoded_list, current_value);
        }
    }

    Py_DECREF(value_iterator);
    Py_DECREF(count_iterator);

    return decoded_list;
}
