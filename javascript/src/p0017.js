/**
 * Project Euler Problem 17
 *
 * I feel like there is a better way to recurse this problem, but I could not
 * think of one at the time
 *
 * Problem:
 *
 * If the numbers 1 to 5 are written out in words: one, two, three, four, five,
 * then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
 *
 * If all the numbers from 1 to 1000 (one thousand) inclusive were written out in
 * words, how many letters would be used?
 *
 * NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and
 * forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20
 * letters. The use of "and" when writing out numbers is in compliance with
 * British usage.
 *
 * @return {number}
 */
exports.p0017 = function() {
    let answer = 0;
    for (let x = 1; x < 1001; x += 1) {
        let string = to_string(x);
        answer += string.split(" ").join("").split("-").join("").length;
    }
    return answer;
}


function to_string(n) {
    if (n >= 1000) {
        let thousands = `${to_string(0 | (n / 1000 % 100))} thousand`;
        if (n % 1000)
            return `${thousands} {to_string(n % 1000)}`;
        return thousands;
    }
    else if (n >= 100) {
        let hundreds = `${to_string(0 | (n / 100 % 10))} hundred`;
        if (n % 100)
            return `${hundreds} and ${to_string(n % 100)}`;
        return hundreds;
    }
    else if (n >= 20) {
        let tens = {
            2: "twenty",
            3: "thirty",
            4: "forty",
            5: "fifty",
            6: "sixty",
            7: "seventy",
            8: "eighty",
            9: "ninety"
        }[0 | (n / 10)];
        if (n % 10)
            return `${tens}-${to_string(n % 10)}`;
        return tens;
    }
    else if (n > 12) {
        let prefix = {
            13: "thir",
            14: "four",
            15: "fif",
            16: "six",
            17: "seven",
            18: "eigh",
            19: "nine"
        };
        return `${prefix[n]}teen`;
    }
    else {
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
        }[n];
    }
}
