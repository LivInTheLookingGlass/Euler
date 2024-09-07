-- Project Euler Problem 17
-- 
-- The key here was remembering I don't need to return the whole string, just the length
-- 
-- Problem:
-- 
-- If the numbers 1 to 5 are written out in words: one, two, three, four, five,
-- then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
-- 
-- If all the numbers from 1 to 1000 (one thousand) inclusive were written out in
-- words, how many letters would be used?
-- 
-- NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and
-- forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20
-- letters. The use of "and" when writing out numbers is in compliance with
-- British usage.

local function to_string_len(n)
    if n >= 1000
    then
        local thousands = to_string_len(n // 1000 % 100) + 8
        if n % 1000 ~= 0
        then
            thousands = thousands + to_string_len(n % 1000)
        end
        return thousands
    end
    if n >= 100
    then
        local hundreds = to_string_len(n // 100 % 10) + 7
        if n % 100 ~= 0
        then
            hundreds = hundreds + 3 + to_string_len(n % 100)
        end
        return hundreds
    end
    if n >= 20
    then
        local tens_t = {
            [2] = 6,
            [3] = 6,
            [4] = 5,
            [5] = 5,
            [6] = 5,
            [7] = 7,
            [8] = 6,
            [9] = 6,
        }
        local tens = tens_t[n // 10]
        if n % 10 ~= 0
        then
            tens = tens + to_string_len(n % 10)
        end
        return tens
    end
    local final = {
        [0] = 4,
        [1] = 3,
        [2] = 3,
        [3] = 5,
        [4] = 4,
        [5] = 4,
        [6] = 3,
        [7] = 5,
        [8] = 5,
        [9] = 4,
        [10] = 3,
        [11] = 6,
        [12] = 6,
        [13] = 8,
        [14] = 8,
        [15] = 7,
        [16] = 7,
        [17] = 9,
        [18] = 8,
        [19] = 8,
    }
    return final[n]
end

return {
    solution = function()
        local answer = 0

        for x = 1,1000,1
        do 
            answer = answer + to_string_len(x)
        end

        return answer
    end
}
