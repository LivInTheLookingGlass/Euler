-- Project Euler Problem 7
--
-- Problem:
--
-- By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that
-- the 6th prime is 13.
--
-- What is the 10 001st prime number?

local primes = loadlib("primes").primes

return {
    solution = function()
        local num
        local idx = 0
        local pgen = primes()

        repeat
            idx = idx + 1
            num = pgen.next()
            print(num)
        until idx > 10001

        return num
    end
}
