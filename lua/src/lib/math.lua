local function factorial(n)
    local answer = 1

    for i = 2,n,1
    do
        answer = answer * i
    end

    return answer
end

local function n_choose_r(n, r)
    if n < 20  -- fast path if number is small
    then
        return factorial(n) / factorial(r) / factorial(n - r)
    end

    -- slow path for big numbers// slow path for larger numbers
    local factors = {}
    local answer
    local tmp

    -- collect factors of final number
    for i = 2,n,1
    do
        factors[i] = 1
    end

    -- negative factor values indicate need to divide
    for i = 2,r,1
    do
        factors[i] = factors[i] - 1
    end
    for i = 2,(n - r),1
    do
        factors[i] = factors[i] - 1
    end

    -- this loop reduces to prime factors only
    for i = n,2,-1
    do
        for j = 2,(i - 1),1
        do
            if i % j == 0
            then
                factors[j] = factors[j] + factors[i]
                factors[i / j] = factors[i / j] + factors[i]
                factors[i] = 0
                break
            end
        end
    end

    local i = 2
    local j = 2
    answer = 1;
    while i <= n
    do
        while factors[i] > 0
        do
            tmp = answer
            answer = answer * i
            while answer < tmp and j <= n
            do
                while factors[j] < 0
                do
                    tmp = math.floor(tmp / j)
                    factors[j] = factors[j] + 1
                end
                j = j + 1;
                answer = tmp * i
            end

            if answer < tmp
            then
                return nil, "math error: overflow"
            end
            factors[i] = factors[i] - 1
        end
        i = i + 1
    end

    while j <= n
    do
        while factors[j] < 0
        do
            answer = answer / j
            factors[j] = factors[j] + 1
        end
        j = j + 1
    end

    return answer
end

return {
    factorial = factorial,
}
