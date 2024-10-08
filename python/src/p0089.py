"""
Project Euler Problem 89

For a number written in Roman numerals to be considered valid there are basic rules which must be followed. Even though
the rules allow some numbers to be expressed in more than one way there is always a "best" way of writing a particular
number.

For example, it would appear that there are at least six ways of writing the number sixteen:

IIIIIIIIIIIIIIII
VIIIIIIIIIII
VVIIIIII
XIIIIII
VVVI
XVI

However, according to the rules only XIIIIII and XVI are valid, and the last example is considered to be the most
efficient, as it uses the least number of numerals.

The 11K text file, roman.txt (right click and 'Save Link/Target As...'), contains one thousand numbers written in
valid, but not necessarily minimal, Roman numerals; see About... Roman Numerals for the definitive rules for this
problem.

Find the number of characters saved by writing each of these in their minimal form.

Note: You can assume that all the Roman numerals in the file contain no more than four consecutive identical units.
"""
from .lib.utils import get_data_file


def parse_roman(roman: str) -> int:
    values = {"I": 1, "V": 5, "X": 10, "L": 50, "C": 100, "D": 500, "M": 1000}
    corrections = {
        "IV": 2,  # initially parsed as 6, but should be 4, so subtract 2
        "IX": 2,  # initially parsed as 11, but should be 9, so subtract 2
        "XL": 20,  # initially parsed as 60, but should be 40, so subtract 20
        "XC": 20,  # initially parsed as 110, but should be 90, so subtract 20
        "CD": 200,  # initially parsed as 600, but should be 400, so subtract 200
        "CM": 200  # initially parsed as 1100, but should be 900, so subtract 200
    }
    number = sum(values[ch] for ch in roman)
    number -= sum(val for key, val in corrections.items() if key in roman)
    return number


def make_roman(i: int) -> str:
    ret = ""
    values = (
        (1000, "M"), (900, "CM"),
        (500, "D"), (400, "CD"),
        (100, "C"), (90, "XC"),
        (50, "L"), (40, "XL"),
        (10, "X"), (9, "IX"),
        (5, "V"), (4, "IV")
    )
    for threshhold, string in values:
        while i >= threshhold:
            ret += string
            i -= threshhold
    return ret + "I" * i


def to_minimal(r: str) -> str:
    return make_roman(parse_roman(r))


def main() -> int:
    saved = 0
    for raw_line in get_data_file('p0089_roman.txt').splitlines():
        line = raw_line.rstrip('\n')
        saved += len(line) - len(to_minimal(line))
    return saved
