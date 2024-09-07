-- Project Euler Problem 2
-- 
-- I modeled this after the C++ solution, because it was by far the simplest
-- 
-- Problem:
-- 
-- Each new term in the Fibonacci sequence is generated by adding the previous two
-- terms. By starting with 1 and 2, the first 10 terms will be:
-- 
-- 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
-- 
-- By considering the terms in the Fibonacci sequence whose values do not exceed
-- four million, find the sum of the even-valued terms.
-- 

return {
    solution = function()
        local answer = 0
        local a = 1
        local b = 2

        while b < 4000000
        do
            answer = answer + b
        
            for j = 1,3,1
            do
                a, b = b, a + b
            end
        end

        return answer
    end
}
