local function primes(stop)
    local p = 2
    local known_primes = {}

    local function next()
        if p < 7
        then
            local ret = p
            local transform = {
                [2] = 3,
                [3] = 5,
                [5] = 7,
            }
            p = transform[p]
            return ret
        end

        while stop == nil or p < stop
        do
            local broken = false
            for i = 1,#known_primes,1
            do
                if p % known_primes[i] ~= 0
                then
                    broken = true
                    break
                end
            end

            local ret = p

            if p % 6 == 1
            then
                p = p + 4
            else
                p = p + 2
            end

            if not broken
            then
                known_primes[#known_primes + 1] = ret
                return ret
            end
        end
    end

    return {
        next = next,
    }
end

local function prime_factors(n)
    local pgen = primes()
    local p = pgen.next()

    local function next()
        print(p .. ", " .. n)
        while p ~= nil and n % p ~= 0
        do
            p = pgen.next()
                print(p)
        end

        if p == nil
        then
            return nil
        end

        if n < 0
        then
            n = -n
            return -1
        end

        n = n / p
        return p
    end

    return {
        next = next,
    }
end

return {
    primes = primes,
    prime_factors = prime_factors,
}
