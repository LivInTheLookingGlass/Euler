-- Project Euler Problem 28
-- 

local function _range_entry(start, stop, step, idx)
    local length = 0
    if step > 0 and start < stop
    then
        length = math.floor(1 + (stop - 1 - start) / step)
    elseif step < 0 and start > stop
    then
        length = math.floor(1 + (start - 1 - stop) / (-step))
    end
    if idx < 0
    then
        idx = length + idx
    end
    if idx < 0 or idx >= length
    then
        return nil, "length is 0, cannot fetch"
    end
    return start + (step * idx)
end

return {
    solution = function()
        local answer = 1
        local range_entry = loadfile("src/lib/range.lua")().range_entry3
        for i = 1,(1000 / 2),1
        do
            local start = (2 * i - 1)^2 + 1
            answer = answer + range_entry(start, 1, (1 * 2 * i - 1))
            answer = answer + range_entry(start, 1, (2 * 2 * i - 1))
            answer = answer + range_entry(start, 1, (3 * 2 * i - 1))
            answer = answer + range_entry(start, 1, (4 * 2 * i - 1))
        end
        return answer
    end
}
