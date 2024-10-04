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

.. f:function:: range_entry4(start, end, step, idx)

    :p integer start:
    :p integer end:
    :p integer step:
    :p integer idx:
    :returns answer: The ``idx``\ :sup:`th` entry of ``start,(end-1),step``
    :rtype answer: integer
    :to: :f:func:`range_entry3`

.. literalinclude:: ../../../../fortran/src/include/ranges.f90
   :language: Fortran
   :linenos:
