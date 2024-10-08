range.lua
=========

View source code :source:`lua/src/lib/range.lua`

.. note::
    
    This module directly ports some of the logic found in Python's :external:py:obj:`range`. Because of that,
    these functions are 0-indexed.

.. lua:function:: range_entry3(start, step, idx)

    :return: ``start + (step * idx)``
    :rtype: number

.. lua:function:: range_entry4(start, stop, step, idx)

    :return: The ``idx``\ :sup:`th` entry of ``start,(stop-1),step``
    :rtype: number

.. literalinclude:: ../../../../lua/src/lib/range.lua
   :language: Lua
   :linenos:
