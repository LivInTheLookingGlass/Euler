return {
    solution = function()
        local answer = 0

        for i = 3,999,3
        do 
            answer = answer + i
        end

        for i = 5,999,5
        do 
            answer = answer + i
        end

        for i = 15,999,15
        do 
            answer = answer - i
        end

        return answer
    end
}
