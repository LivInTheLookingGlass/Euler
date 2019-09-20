exports.main = function()   {
// for a proof on why this formulation works, see python/p0002.py
    let answer = 0;
    let i = 2;
    let j = 8;
    let tmp = 0;
    while (i < 4000000) {
        answer += i;
        tmp = 4 * j + i;
        i = j;
        j = tmp;
    }
    return answer;
}
