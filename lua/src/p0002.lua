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
