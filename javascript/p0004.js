/**
 * Project Euler Problem 4
 *
 * I couldn't figure out how to do this as efficiently as I would have liked. I am
 * SURE that there is a better way to check if a number is a palindrome, but I
 * could not think of one.
 *
 * Problem:
 *
 * A palindromic number reads the same both ways. The largest palindrome made from
 * the product of two 2-digit numbers is 9009 = 91 × 99.
 *
 * Find the largest palindrome made from the product of two 3-digit numbers.
 *
 * @return {number}
 **/
exports.p0004 = function() {
    let answer = 0;
    for (let v = 101; v < 1000; v++)
    {
        for (let u = 100; u < v; u++)
        {
            let p = u * v.toString();
            let ps = p.toString();
            if (ps === ps.split("").reverse().join("") && p > answer)
            {
                answer = p;
            }
        }
    }
    return answer;
};
