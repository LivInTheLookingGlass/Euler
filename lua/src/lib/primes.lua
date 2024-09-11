local function primes(stop)
    local prime = 1
    local candidate = 2
    local sieve = {}

    local function next()
        if stop ~= nil and candidate > stop
        then
            return nil
        end

        while true
        do
            candidate = prime + 1
            local steps = sieve[candidate]
            if steps == nil
            then
                sieve[candidate * candidate] = { candidate }
                prime = candidate
                return candidate
            else
                for i = 1,#steps,1
                do
                    local step = steps[i]
                    local value = candidate + step
                    local newlist = sieve[value]
                    if newlist ~= nil
                    then
                        newlist[#newlist + 1] = value
                    else
                        sieve[candidate + value] = { value }
                    end
                end

                sieve[candidate] = nil
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
