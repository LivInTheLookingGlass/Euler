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

local factorial = loadlib('math').factorial

return {
    solution = function()
        local answer = 0

        for x = 10,99999 do
            local xs = tostring(x)
            local sum = 0
            for i = 1,#xs do
                sum = sum + factorial(tonumber(xs:sub(i, i)))
            end

            if sum == x then
                answer = answer + x
            end
        end

        return answer
    end
}
