utils.f90
=========

View source code :source:`fortran/include/utils.f90`

.. f:module:: utils

.. f:function:: utils/get_data_file(filename)

    Given the name of a file in ``/_data``, this function returns the entirety of its contents,
    or an empty string if there is an error.

    :p character(len=*) filename:
    :returns contents:
    :rtype contents: character(len=:)
    :rattrs contents: allocatable

.. literalinclude:: ../../../../fortran/src/include/utils.f90
   :language: Fortran
   :linenos:

.. tags:: file-io
