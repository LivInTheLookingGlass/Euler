utils.f90
=========

View source code :source:`fortran/include/utils.f90`

.. f:module:: utils

.. f:function:: get_data_file(filename)

    Given the name of a file in ``/_data`` (where ``/`` is the repository root), this function returns
    the entirety of its contents, or an empty string if there is an error.

    :p character(len=*) filename:
    :returns contents:
    :rtype contents: character(len=:)
    :rattrs contents: allocatable

.. f:function:: get_answer(id)

    Return the answer to a given problem, as represented in ``/_data/answers.tsv``

    :p integer(i4d) id:
    :returns answer:
    :rtype answer: AnswerT

.. f:type:: AnswerT

    This stores the answer to a generic problem, storing multiple potential types. If the type field contains
    :f:var:`errort`, there was an error in generating the answer. If it is :f:var:`int64t`, it holds data of
    type ``integer(i19t)``. If it is :f:var:`stringt`, it holds an allocatable character array.

    :f integer(i19t) int_value:
    :f character(len=:) string_value:
    :fattrs string_value: allocatable
    :f integer(i1d) type:

.. literalinclude:: ../../../../fortran/src/include/utils.f90
   :language: Fortran
   :linenos:

.. tags:: file-io
