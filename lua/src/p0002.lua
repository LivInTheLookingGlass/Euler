return {
    solution = function()
        answer = 0
        a = 1
        b = 2

        while b < 4000000
        do
            answer = answer + b
        
            for j = 0,2,1
            do
                t = b
                b = a + b
                a = t
            end
        end

        return answer
    end
}
