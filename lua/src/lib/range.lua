-- This file is a direct port of Python's range functions

local function range_entry3(start, step, idx)
    return start + (step * idx)
end

local function range_entry4(start, stop, step, idx)
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
    return range_entry3(start, step, idx)
end

return {
    range_entry3 = range_entry3,
    range_entry4 = range_entry4,
}
