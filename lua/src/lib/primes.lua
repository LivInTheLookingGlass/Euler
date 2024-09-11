local function primes(stop)
    local prime = 1
    local candidate = 2
    local sieve = {}

    local function next_prime(candidate)
        local steps = sieve[candidate]

        if steps
        then
            for _, step in ipairs(steps)
            do
                local value = candidate + step
                local newlist = sieve[value]
                if newlist
                then
                    table.insert(newlist, value)
                else
                    sieve[value] = { value }
                end
            end
            sieve[candidate] = nil
            return next_prime(candidate + 1)
        else
            sieve[candidate * candidate] = { candidate }
            return candidate
        end
    end

    local function next()
        if stop ~= nil and prime >= stop
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
        print(p .. ", " .. n)
        while p ~= nil and n % p ~= 0
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
