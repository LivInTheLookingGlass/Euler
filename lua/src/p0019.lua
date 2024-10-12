-- Project Euler Problem 19
--
-- This one ended up being very easy thanks to the time library
--
-- Problem:
--
-- You are given the following information, but you may prefer to do some research
-- for yourself.
--
--     1 Jan 1900 was a Monday.
--     Thirty days has September,
--     April, June and November.
--     All the rest have thirty-one,
--     Saving February alone,
--     Which has twenty-eight, rain or shine.
--     And on leap years, twenty-nine.
--     A leap year occurs on any year evenly divisible by 4, but not on a century
--     unless it is divisible by 400.
--
-- How many Sundays fell on the first of the month during the twentieth century
-- (1 Jan 1901 to 31 Dec 2000)?

local function is_sunday(year, month, day)
    return os.date("*t", os.time({year=year, month=month, day=day})).wday == 1
end

return {
    solution = function()
        local answer = 0
        for year = 1901, 2000 do
            for month = 1, 12 do
                if is_sunday(year, month, 1) then
                    answer = answer + 1
                end
            end
        end
        return answer
    end
}
