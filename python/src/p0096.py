# from math import sqrt
# from typing import NamedTuple, Sequence, Set, Tuple

# TSet = Set[int]
# TSeqSet = Sequence[TSet]
# TSeqSeqSet = Sequence[TSeqSet]
# TSeqSeqSeqSet = Sequence[TSeqSeqSet]

# TRowCol = Tuple[int, int]
# TSquareCoord = Tuple[int, int, int]

# class Grid(NamedTuple):
#     n: int  # minor squares are n x n
#     n2: int  # grid is n2 x n2
#     cells: TSeqSet
#     rows: TSeqSeqSet
#     cols: TSeqSeqSet
#     squares: TSeqSeqSeqSet
#     row_has: TSeqSet
#     col_has: TSeqSet
#     square_has: TSeqSeqSet

#     def __new__(cls, n2: int = 9):
#         n = int(sqrt(n2))
#         if n * n != n2:
#             raise ValueError("Grid size must be a perfect square")

#         cells = tuple(set(range(1, n2 + 1)) for _ in range(n2 * n2))
#         rows = tuple(cells[idx * n2:(idx + 1) * n2] for idx in range(n2))
#         cols = tuple(tuple(rows[idx][col] for idx in range(n2)) for col in range(n2))
#         squares = tuple(
#             tuple(
#                 tuple(rows[row * n + (idx // n)][col * n + (idx % n)] for idx in range(n2 * n2))
#                 for col in range(n)
#             ) for row in range(n)
#         )
#         row_has = tuple(set() for _ in range(n2))
#         col_has = tuple(set() for _ in range(n2))
#         square_has = tuple(tuple(set() for _ in range(n)) for _ in range(n))

#         return super().__new__(cls, n, n2, cells, rows, cols, squares, row_has, col_has, square_has)

#     def row_col_to_cell(self, row: int, col: int) -> int:
#         return row * self.n2 + col

#     def cell_to_row_col(self, cell_index: int) -> TRowCol:
#         return divmod(cell_index, self.n2)

#     def row_col_to_square(self, row: int, col: int) -> TSquareCoord:
#         return (row // self.n, col // self.n, (row % self.n) * self.n + (col % self.n))

#     def square_to_row_col(self, square_row: int, square_col: int, idx_in_square: int) -> TRowCol:
#         return (square_row * self.n + idx_in_square // self.n, square_col * self.n + idx_in_square % self.n)

#     def final_value(self, row: int, col: int) -> int:
#         cell_values = self.rows[row][col]
#         if len(cell_values) == 1:
#             return next(iter(cell_values))
#         raise ValueError(f"Cell at row {row}, col {col} still has a superposition: {cell_values}")
