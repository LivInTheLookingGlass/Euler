utils.f90
=========

View source code :source:`fortran/include/utils.f90`

.. f:module:: utils

.. f:function:: get_answer(id)

    Return the answer to a given problem, as represented in ``/_data/answers.tsv``, where ``/`` is the repository root.
    On first run, it will take ``O(n)`` time, where ``n`` is the number of problems in the file. From there on out, it
    should be ``O(1)``.

    :p integer(i4t) id:
    :returns answer:
    :rtype answer: AnswerT

.. f:type:: AnswerT

    This stores the answer to a generic problem, storing multiple potential types. If the type field contains
    :f:var:`errort`, there was an error in generating the answer. If it is :f:var:`int64t`, it holds data of
    type ``integer(i18t)``. If it is :f:var:`stringt`, it holds a character array.

    :f integer(i1t) type:
    :f integer(i18t) int_value:
    :f string_value:
    :ftype string_value: character(len=ANSWERT_STR_LEN)

.. literalinclude:: ../../../../fortran/src/include/utils.f90
   :language: Fortran
   :linenos:

.. tags:: file-io
