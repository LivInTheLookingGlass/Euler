local function primes(stop)
    local prime = 1
    local candidate = 2
    local sieve = {}

    local function next_prime(cand)
        local steps = sieve[cand]

        if steps
        then
            for _, step in ipairs(steps)
            do
                local value = cand + step
                local newlist = sieve[value]
                if newlist
                then
                    table.insert(newlist, value)
                else
                    sieve[value] = { value }
                end
            end
            sieve[cand] = nil
            return next_prime(cand + 1)
        else
            sieve[cand * cand] = { cand }
            return cand
        end
    end

    local function next()
        if stop and prime >= stop
        then
            sieve = {}
            error("Tried to exceed given limit")
        end

        prime = next_prime(candidate)
        candidate = prime + 1
        return prime
    end

    return {
        next = next
    }
end

local function prime_factors(n)
    local pgen = primes()
    local p = pgen.next()

    local function next()
        if n == 1
        then
            return nil
        end

        while p and n % p ~= 0
        do
            p = pgen.next()
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

        n = math.floor(n / p)
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
