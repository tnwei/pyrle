char rle_module_doc[] = "\n\
Performs run-length encoding and decoding of a sequence in real time.\n\
\n\
Module containing C Extension for RLE operations on large sequences.\n\
\n\
Methods\n\
-------\n\
encode: performs run-length encoding of given sequence\n\
decode: performs run-length decoding of given sequence\n\
\n\
Usage\n\
-----\n\
\n\
# import module\n\
import rle.rle_fast as rle\n\
\n\
# perform encoding on sequence 'a'\n\
values, counts = rle.encode(a)\n\
\n\
# decode the values and counts to recover original sequence\n\
sequence = rle.decode(values, counts)\n\
";

char encode_doc[] = "\n\
Encodes run-length encoding of given iterable.\n\
\n\
Parameters\n\
----------\n\
seq: Any Python iterable, e.g.  lists, strings, tuples,\n\
    pandas Series, to perform run-length encoding on.\n\
\n\
Returns\n\
-------\n\
values, counts: list of contiguous unique values, and list of\n\
    counts\n\
";

char decode_doc[] = "\n\
Decodes run-length encoding of given iterable.\n\
\n\
Parameters\n\
----------\n\
values, counts: List of contiguous unique values, and list of counts\n\
\n\
Returns\n\
-------\n\
seq: Decoded sequence\n\
";
