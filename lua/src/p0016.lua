-- Project Euler Problem 15
--
-- Problem:
--
-- 2**15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
--
-- What is the sum of the digits of the number 2**1000?

return {
    solution = function()
        local numbers = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        local ten15 = 1000000000000000
        local power = 1
        local answer = 0

        for i = 1,1000 do
            for j = 1,#numbers do
                numbers[j] = numbers[j] * 2
            end
            for j = 1,(#numbers - 1) do
                if (numbers[j] > ten15) then
                    numbers[j + 1] = numbers[j + 1] + math.floor(numbers[j] / ten15)
                    numbers[j] = numbers[j] % ten15
                end
            end
        end
        for i = 1, 18 do
            for j = 1,#numbers do
                answer = answer + math.floor(numbers[j] / power) % 10
            end
            power = power * 10
        end
        return answer
    end
}
