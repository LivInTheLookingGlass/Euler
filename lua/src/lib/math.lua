local function factorial(n)
    local answer = 1

    for i = 2,n,1
    do
        answer = answer * i
    end

    return answer
end

return {
    factorial = factorial,
}
