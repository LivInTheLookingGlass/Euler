-- Project Euler Problem 9
--
-- This was pretty fun to port
--
-- Problem:
--
-- A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
-- a**2 + b**2 = c**2
--
-- For example, 3**2 + 4**2 = 9 + 16 = 25 = 5**2.
--
-- There exists exactly one Pythagorean triplet for which a + b + c = 1000.
-- Find the product abc.

return {
    solution = function()
        local c = 3

        while true
        do
            local c_square = c * c

            for b = 2,c,1
            do
                local b_square = b * b

                for a = 1,b,1
                do
                    local a_square = a * a

                    if a_square + b_square == c_square and a + b + c == 1000
                    then
                        return a * b * c
                    end
                end
            end
            c = c + 1
        end
    end
}
