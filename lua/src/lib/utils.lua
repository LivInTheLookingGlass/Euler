local function get_data_file(name, mode)
    local file = io.open("../_data/" .. name, mode)

    if not file then
        print("Could not open file: " .. filename)
        return
    end

    local contents = file:read("*a")  -- Read all contents
    file:close()
    return contents
end

local function get_answer(id)
    local id_str = tostring(id)
    for line in string.gmatch(get_data_file("answers.tsv", "r"), "[^\r\n]+") do
        local row = {} -- {id, type, length, value}
        for val in string.gmatch(line, "[^\t]+") do
            table.insert(row, val)
        end
        if id_str == row[1] then
            local type_ = row[2]
            local length = tonumber(row[3])
            local value = row[4]
            
            if type_ == 'str' then
                return value
            else if type_ == 'int' then
                return tonumber(value)
            else if type_ == 'uint' then
                if length < 64 then
                    return tonumber(value)
                end
                local parsed = tonumber(value)
                if tostring(parsed) == value then
                    return parsed
                end
                return nil, "Value too big to properly parse"
            end
        end
    end
end

return {
    get_data_file = get_data_file,
    get_answer = get_answer,
}
