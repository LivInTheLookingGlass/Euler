"""
Project Euler Problem 17

I feel like there is a better way to recurse this problem, but I could not
think of one at the time

Problem:

If the numbers 1 to 5 are written out in words: one, two, three, four, five,
then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in
words, how many letters would be used?

NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and
forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20
letters. The use of "and" when writing out numbers is in compliance with
British usage.
"""


def to_string(n: int) -> str:
    if n >= 1000:
        thousands = "{} thousand".format(to_string(n // 1000 % 100))
        if n % 1000:
            return "{} {}".format(thousands, to_string(n % 1000))
        return thousands
    elif n >= 100:
        hundreds = "{} hundred".format(to_string(n // 100 % 10))
        if n % 100:
            return "{} and {}".format(hundreds, to_string(n % 100))
        return hundreds
    elif n >= 20:
        tens = {
            2: "twenty",
            3: "thirty",
            4: "forty",
            5: "fifty",
            6: "sixty",
            7: "seventy",
            8: "eighty",
            9: "ninety"
        }[n // 10]
        if n % 10:
            return "{}-{}".format(tens, to_string(n % 10))
        return tens
    elif n > 12:
        prefix = {
            13: "thir",
            14: "four",
            15: "fif",
            16: "six",
            17: "seven",
            18: "eigh",
            19: "nine"
        }
        return "{}teen".format(prefix[n])
    else:
        return {
            0: "zero",
            1: "one",
            2: "two",
            3: "three",
            4: "four",
            5: "five",
            6: "six",
            7: "seven",
            8: "eight",
            9: "nine",
            10: "ten",
            11: "eleven",
            12: "twelve"
        }[n]


def main() -> int:
    answer = 0
    for x in range(1, 1001):
        string = to_string(x)
        answer += len(string.replace(" ", "").replace("-", ""))
    return answer


if __name__ == '__main__':
    print(main())  # pragma: no cover
