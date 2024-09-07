return {
    solution = function()
        local sum = 1
        local sum_of_squares = 1
        for i = 2,100,1
        do
            sum = sum + i
            sum_of_squares = sum_of_squares + (i * i)
        end
        return (sum * sum) - sum_of_squares;
    end
}

