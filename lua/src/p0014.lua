-- Project Euler Problem 14
--
-- Problem:
--
-- The following iterative sequence is defined for the set of positive integers:
--
-- n → n/2 (n is even)
-- n → 3n + 1 (n is odd)
--
-- Using the rule above and starting with 13, we generate the following sequence:
-- 13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
--
-- It can be seen that this sequence (starting at 13 and finishing at 1) contains
-- 10 terms. Although it has not been proved yet (Collatz Problem), it is thought
-- that all starting numbers finish at 1.
--
-- Which starting number, under one million, produces the longest chain?
--
-- NOTE: Once the chain starts the terms are allowed to go above one million.

local function collatz_len(n, cache)
    if cache[n] then
        return cache[n]
    end

    local result
    if n == 1 then
        result = 0
    elseif n % 2 == 0 then
        result = 1 + collatz_len(math.floor(n / 2), cache)
    else
        result = 2 + collatz_len(math.floor((3 * n + 1) / 2), cache)
    end

    cache[n] = result
    return result
end

return {
    solution = function()
        local max_seen = 0
        local answer = 0
        local cache = {}

        for i = 1,999999 do
            local result = collatz_len(i, cache)
            if result > max_seen then
                max_seen = result
                answer = i
            end
        end

        return answer
    end
}
