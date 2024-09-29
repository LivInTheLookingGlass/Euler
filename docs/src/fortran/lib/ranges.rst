ranges.f90
==========

View source code :source:`fortran/include/ranges.f90`

.. f:module:: ranges

.. f:function:: range_entry3(start, step, idx)

    :p integer start:
    :p integer step:
    :p integer idx:
    :returns answer: start + (step * idx)
    :rtype answer: integer

.. f:function:: range_entry4(start, stop, step, idx)

    :p integer start:
    :p integer stop:
    :p integer step:
    :p integer idx:
    :returns answer: The ``idx``\ :sup:`th` entry of ``start,(stop-1),step``
    :rtype answer: integer

.. literalinclude:: ../../../../fortran/src/include/ranges.f90
   :language: Fortran
   :linenos:
