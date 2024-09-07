return {
    solution = function()
        local c = 3
        while true
        do
            local c_square = c * c
            for b = 2,c,1
            do
                local b_square = b * b
                for a = 1,b,1
                do
                    local a_square = a * a
                    if a_square + b_square == c_square and a + b + c == 1000
                    then
                        return a * b * c
                    end
                end
            end
            c = c + 1
        end
    end
}
