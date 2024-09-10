local function primes(stop)
    local p = 2
    local known_primes = {}

    local function next()
        if p == 2
        do
            p = 3
            known_primes[0] = 2
            return 2
        end

        while stop == nil or p < stop
        do
            local broken = false
            for i = 1,#known_primes,1
            do
                if p % known_primes[0] ~= 0
                then
                    broken = true
                    break
                end
            end

            p = p + 2
            if not broken
            then
                known_primes[#known_primes + 1] = p - 2
                return p - 2
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
        while p ~= nil and n % p != 0
        do
            p = pgen.next()
        end

        if p == nil
        then
            return nil
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
