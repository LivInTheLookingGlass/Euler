-- Project Euler Problem 3
--
-- Problem:
--
-- The prime factors of 13195 are 5, 7, 13 and 29.
--
-- What is the largest prime factor of the number 600851475143 ?

return {
    solution = function()
        local fgen = prime_factors(600851475143)
        local f = 0
        local answer = 0

        while (f = fgen.next()) ~= nil
        do
            answer = f
        end

        return answer
    end
}
