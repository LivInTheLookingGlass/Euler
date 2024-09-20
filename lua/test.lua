local has_luacov = package.loaded['luacov'] ~= nil

function loadlib(...)
    local libname = select(1, ...)
    local length = select("#", ...)

    local lib, err = loadfile("src/lib/" .. select(1, ...) .. ".lua")
    if not lib then
        error("Failed to load lib " .. libname .. ": " .. err)
    end
    lib = lib()

    if length == 1 then
        return lib
    end

    local ret = {}
    for i = 2,length do
        local fname = select(i, ...)
        ret[fname] = lib[fname]
    end
    return ret
end

-- Function to load a problem solution file
local function load_problem(file_name)
    local func, err = loadfile(file_name)

    if not func then
        error("Failed to load file " .. file_name .. ": " .. err)
    end

    local chunk = func()

    if type(chunk) ~= "table" or not chunk.solution then
        error("File " .. file_name .. " must return a table with a 'solution' function")
    end

    return chunk.solution
end

-- Timing and result check function
local function check_problem(file_name, expected_answer, is_slow, problem_name)
    print("Starting: " .. file_name)
    local problem_func = load_problem("src/" .. file_name)
    if is_slow and has_luacov then
        return
    end
    local start_time = os.clock()
    local success, result = pcall(problem_func)
    local elapsed_time = os.clock() - start_time

    if not success then
        error("Error executing " .. problem_name .. ": " .. result)
    end

    if result ~= expected_answer then
        error(
            "Problem " .. problem_name .. " returned " .. tostring(result) .. ", but expected " ..
            tostring(expected_answer)
        )
    end

    if not is_slow and not has_luacov and elapsed_time > 60 then
        error(
            "Problem " .. problem_name .. " took ~" .. string.format("%.3f", elapsed_time) ..
            "s, exceeding the expected time limit of 60s."
        )
    end

    print("Problem " .. problem_name .. " passed (in ~" .. string.format("%.3f", elapsed_time) .. "s).")
end

local get_answer = loadlib("utils").get_answer

-- Problems configuration: filename -> {expected_answer, is_slow}
local problems = {}

for i = 1, 11 do
    problems[string.format("p%04d.lua", i)] = {get_answer(i), false}
end
for i = 13, 15 do
    problems[string.format("p%04d.lua", i)] = {get_answer(i), false}
end

local more_problems = {
    ["p0017.lua"] = {get_answer(17), false},
    ["p0028.lua"] = {get_answer(28), false},
    ["p0034.lua"] = {get_answer(34), false},
    ["p0076.lua"] = {get_answer(76), true},
    ["p0836.lua"] = {get_answer(836), false},
}

for _, v in ipairs(more_problems) do
    table.insert(problems, v)
end

-- Fast testing loop
for file_name, config in pairs(problems) do
    if not config[2] then
        check_problem(file_name, config[1], config[2], file_name:match("(%d+)"))
    end
end

-- Slow testing loop
for file_name, config in pairs(problems) do
    if config[2] then
        check_problem(file_name, config[1], config[2], file_name:match("(%d+)"))
    end
end
