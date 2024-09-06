return {
    solution = function()
        answer = 0

        for i = 3,1000,3
        do 
            answer = answer + i
        end

        for i = 5,1000,5
        do 
            answer = answer + i
        end

        for i = 15,1000,15
        do 
            answer = answer - i
        end

        return answer
    end
}
