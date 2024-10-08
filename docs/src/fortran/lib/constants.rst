constants.f90
=============

View source code :source:`fortran/include/constants.f90`

.. f:module:: constants

.. f:variable:: i1t
    :type: integer
.. f:variable:: i2t
    :type: integer
.. f:variable:: i4t
    :type: integer
.. f:variable:: i18t
    :type: integer

    A set of digit type constraints that denote how many decimal digits a number can support.
    They are given as ``i<len>t`` or ``r<len>_<exp>t``

.. f:variable:: errort
    :type: integer(i1t)
.. f:variable:: int64t
    :type: integer(i1t)
.. f:variable:: stringt
    :type: integer(i1t)

    Denotes the type of an :f:type:`AnswerT`

.. f:variable:: ERROR_ANSWER_MISMATCH
    :type: integer
.. f:variable:: ERROR_ANSWER_TIMEOUT
    :type: integer
.. f:variable:: ERROR_ANSWER_TYPE_MISMATCH
    :type: integer
.. f:variable:: ERROR_PRIME_ALLOCATE_FAILED
    :type: integer
.. f:variable:: ERROR_UTILS_ALLOCATE_FAILED
    :type: integer
.. f:variable:: ERROR_FILE_READ_FAILED
    :type: integer
.. f:variable:: ERROR_PROB_ALLOCATE_FAILED
    :type: integer

    Denotes the exit codes of different failure modes, counting up from 1

.. f:variable:: DATA_MAX_NAME_SIZE
    :type: integer
.. f:variable:: ANSWERT_STR_SIZE
    :type: integer

    Denotes the size of certain variables

.. literalinclude:: ../../../../fortran/src/include/constants.f90
   :language: Fortran
   :linenos:

.. tags:: constants
