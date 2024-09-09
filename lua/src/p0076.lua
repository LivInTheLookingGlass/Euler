-- Project Euler Problem 34
--
-- This ended up being a filtering problem. The problem with my solution is that I
-- am not satisfied with my filter at all. I feel like there is a more efficient
-- way to go about it.
--
-- Problem:
--
-- 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
--
-- Find the sum of all numbers which are equal to the sum of the factorial of
-- their digits.
--
-- Note: as 1! = 1 and 2! = 2 are not sums they are not included.

local factorial = loadfile('src/lib/math.lua')().factorial

return {
    solution = function()
        local answer = 0
        local idx = 0
        local sum = 100
        local counts = {}

        for i = 1, 101 do
            counts[i] = 0
        end

        counts[2 + 1] = 0

        while counts[100 + 1] == 0
        do
            counts[2 + 1] = counts[2 + 1] + 2

            if sum >= 100
            then
                answer = answer + (100 + counts[2 + 1] - sum) / 2
                idx = 2
                
                repeat
                    idx = idx + 1
                    counts[idx] = 0  -- please remember lua is 1-indexed
                    idx = idx + 1
                    counts[idx] = counts[idx] + idx - 1

                    for i = (idx - 1),101,1
                    do
                        sum = sum + counts[i]
                    end
                until sum <= 100
            end

            sum = 0
            for i = 1,101,1
            do
                sum = sum + counts[i]
            end
        end

        return answer
    end
}
