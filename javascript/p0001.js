exports.main = function()   {
    let answer = 0;
    for (let i = 3; i < 1000; i += 3)    {
        answer += i;
    }
    for (let i = 5; i < 1000; i += 5)    {
        answer += i;
    }
    for (let i = 15; i < 1000; i += 15)    {
        answer -= i;
    }
    return answer;
}