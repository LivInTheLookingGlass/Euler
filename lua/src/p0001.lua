-- Project Euler Question 1
--
-- I did it the old-fashioned way in this language
--
-- Problem:
--
-- If we list all the natural numbers below 10 that are multiples of 3 or 5, we
-- get 3, 5, 6 and 9. The sum of these multiples is 23.
--
-- Find the sum of all the multiples of 3 or 5 below 1000.

return {
    solution = function()
        local answer = 0

        for i = 3,999,3 do
            answer = answer + i
        end

        for i = 5,999,5 do
            answer = answer + i
        end

        for i = 15,999,15 do
            answer = answer - i
        end

        return answer
    end
}
