-- Project Euler Problem 20
--
-- Problem:
--
-- n! means n × (n − 1) × ... × 3 × 2 × 1
--
-- For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
-- and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
--
-- Find the sum of the digits in the number 100!

return {
    solution = function()
        local power = 1
        local answer = 0
        local ten16 = 10000000000000000
        local numbers = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        for i = 2,100 do
            for j = 1,#numbers do
                numbers[j] = numbers[j] * i
            end
            for j = 1,(#numbers - 1) do
                if (numbers[j] > ten16) then
                    numbers[j + 1] = numbers[j + 1] + math.floor(numbers[j] / ten16)
                    numbers[j] = numbers[j] % ten16
                end
            end
        end
        for i = 1,16 do
            for j = 1,#numbers do
                answer = answer + math.floor(numbers[j] / power) % 10
            end
            power = power * 10
        end
        return answer
    end
}
