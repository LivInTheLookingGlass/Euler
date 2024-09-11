-- Project Euler Problem 7
--
-- Problem:
--

local primes = loadlib("primes").primes

return {
    solution = function()
        local num
        local idx = 0
        local pgen = primes()

        repeat
            idx = idx + 1
            num = pgen.next()
            print(idx .. ", " .. num)
        until idx > 10000

        return num
    end
}
