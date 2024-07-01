/**
* Project Euler Problem 1
* 
* Did this the old fashioned way, because this was before I figured out the closed form solution
* 
* Problem:
* 
* If we list all the natural numbers below 10 that are multiples of 3 or 5, we
* get 3, 5, 6 and 9. The sum of these multiples is 23.
* 
* Find the sum of all the multiples of 3 or 5 below 1000.
*/
exports.p0001 = function() {
    let answer = 0;
    for (let i = 3; i < 1000; i += 3) {
        answer += i;
    }
    for (let i = 5; i < 1000; i += 5) {
        answer += i;
    }
    for (let i = 15; i < 1000; i += 15) {
        answer -= i;
    }
    return answer;
};
