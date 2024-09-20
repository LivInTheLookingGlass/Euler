utils.lua
=========

View source code :source:`lua/src/lib/utils.lua`

.. lua:function:: get_data_file(name, mode)

    :return: The contents of a file in ``/_data``
    :rtype: string

.. lua:function:: get_answer(id)

    :return: The answer to a specific problem, as stored in ``/_data/answers.tsv``
    :rtype: number | string

.. literalinclude:: ../../../../lua/src/lib/utils.lua
   :language: Lua
   :linenos:
