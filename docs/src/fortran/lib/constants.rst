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

.. literalinclude:: ../../../../fortran/src/include/constants.f90
   :language: Fortran
   :linenos:

.. tags:: constants
