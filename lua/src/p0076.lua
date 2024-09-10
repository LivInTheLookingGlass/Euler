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

return {
    solution = function()
        local answer = 0
        local idx
        local sum = 100
        local counts = {}

        for i = 2,100,1
        do
            counts[i] = 0
        end

        counts[2] = 100

        while counts[100] == 0
        do
            counts[2] = counts[2] + 2

            if sum >= 100
            then
                answer = answer + math.floor((100 + counts[2] - sum) / 2)
                idx = 2

                repeat
                    counts[idx] = 0
                    idx = idx + 1
                    counts[idx] = counts[idx] + idx

                    sum = counts[idx]
                    for i = (idx+1),100,1
                    do
                        sum = sum + counts[i]
                    end
                until sum <= 100
            end

            sum = counts[2]
            for i = 3,100,1
            do
                sum = sum + counts[i]
            end
        end

        return answer
    end
}
