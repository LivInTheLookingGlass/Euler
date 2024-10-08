-- Project Euler Problem 22
--
-- Problem:
--
-- Using names.txt (right click and 'Save Link/Target As...'), a 46K text file
-- containing over five-thousand first names, begin by sorting it into
-- alphabetical order. Then working out the alphabetical value for each name,
-- multiply this value by its alphabetical position in the list to obtain a name
-- score.
--
-- For example, when the list is sorted into alphabetical order, COLIN, which is
-- worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would
-- obtain a score of 938 × 53 = 49714.
--
-- What is the total of all the name scores in the file?

local get_data_file = loadlib("utils").get_data_file

return {
    solution = function()
        local answer = 0
        local array = {get_data_file("p0022_names.txt"):gsub('"', ''):gmatch("([^,]+)")}
        table.sort(array)
        for idx, name in ipairs(array) do
            local score = 0
            for i = 1,#name do
                score = score + string.byte(name, i) - string.byte('A', 1) + 1
            end
            answer = answer + score * idx
        end
        return answer
    end
}
