-- Project Euler Problem 5
--
-- Problem:
--

local prime_factors = loadlib("primes").prime_factors

return {
    solution = function()
        local answer = 1
        local factorTracker = {}
        local localFactorTracker = {}
        for i = 1,20 do
            factorTracker[i] = 0
            localFactorTracker[i] = 0
        end

        for i = 2,20 do
            local pf = prime_factors(i)
            local p = pf.next()
            repeat
                localFactorTracker[p] = localFactorTracker[p] + 1
                p = pf.next()
            until not p

            for j = 2,19 do
                if factorTracker[j] < localFactorTracker[j] then
                    factorTracker[j] = localFactorTracker[j]
                end
                localFactorTracker[j] = 0
            end
        end
        for i = 2,19 do
            for j = 1,factorTracker[i] do
                answer = answer * i
            end
        end

        return answer
    end
}
