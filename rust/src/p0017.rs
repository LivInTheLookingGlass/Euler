/*
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
*/

fn to_string(n: u16) -> String {
    if n >= 1000 {
        let mut thousands = to_string(n / 1000 % 100);
        thousands.push_str(&" thousand");
        if n % 1000 != 0 {
            thousands.push_str(" ");
            thousands.push_str(&to_string(n % 1000));
        }
        return thousands;
    }
    if n >= 100 {
        let mut hundreds = to_string(n / 100 % 10);
        hundreds.push_str(&" hundred");
        if n % 100 != 0 {
            hundreds.push_str(&" and ");
            hundreds.push_str(&to_string(n % 100));
        }
        return hundreds;
    }
    if n >= 20 {
        let mut tens = match n / 10 {
            2 => "twenty",
            3 => "thirty",
            4 => "forty",
            5 => "fifty",
            6 => "sixty",
            7 => "seventy",
            8 => "eighty",
            9 => "ninety",
            _ => unreachable!()
        }.to_owned();
        if n % 10 != 0 {
            tens.push_str(&"-");
            tens.push_str(&to_string(n % 10));
        }
        return tens;
    }
    if n > 12 {
        let mut prefix = match n {
            13 => "thir",
            14 => "four",
            15 => "fif",
            16 => "six",
            17 => "seven",
            18 => "eigh",
            19 => "nine",
            _ => unreachable!()
        }.to_owned();
        prefix.push_str(&"teen");
        return prefix;
    }
    return match n {
        0 => "zero",
        1 => "one",
        2 => "two",
        3 => "three",
        4 => "four",
        5 => "five",
        6 => "six",
        7 => "seven",
        8 => "eight",
        9 => "nine",
        10 => "ten",
        11 => "eleven",
        12 => "twelve",
        _ => unreachable!()
    }.to_owned();
}


pub fn p0017() -> i128 {
    let mut answer: u16 = 0;
    for x in 1..=1000 {
        let string = to_string(x);
        answer += string.replace(" ", "").replace("-", "").len() as u16;
    }
    return answer.into();
}
