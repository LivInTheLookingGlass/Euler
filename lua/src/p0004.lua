-- Project Euler Problem 4
--
-- Problem:
--
-- A palindromic number reads the same both ways. The largest palindrome made from
-- the product of two 2-digit numbers is 9009 = 91 × 99.
--
-- Find the largest palindrome made from the product of two 3-digit numbers.

return {
    solution = function()
        local answer = 0

        for v = 101,999 do
            for u = 100,(v-1) do
                local p = u * v
                local ps = tostring(p)

                if ps == string.reverse(ps) and p > answer then
                    answer = p
                end
            end
        end

        return answer
    end
}
