-- Project Euler Problem 10
--
-- Problem:
--
-- The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
--
-- Find the sum of all the primes below two million.

local primes = loadlib("primes").primes

return {
    solution = function()
        local answer = 0
        local pg = primes(2000000)
        local tmp = pg.next()

        repeat
            answer = answer + tmp
            tmp = pg.next()
        until tmp == nil

        return answer;
    end
}
