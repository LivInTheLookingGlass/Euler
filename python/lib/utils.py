from pathlib import Path
from typing import Any, overload

try:
    from typing import Literal
except ImportError:
    from typing_extensions import Literal  # type: ignore


@overload
def get_data_file(name: str, mode: Literal['r'] = 'r') -> str: ...
@overload
def get_data_file(name: str, mode: Literal['rb']) -> bytes: ...


def get_data_file(name: str, mode: str = 'r') -> Any:
    """Returns the contents of a file in the top-level _data directory."""
    with Path(__file__).parent.parent.parent.joinpath('_data', name).open(mode) as f:
        return f.read()
