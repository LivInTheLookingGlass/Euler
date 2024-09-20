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
local problems = {
    ["p0001.lua"] = {get_answer(1), false},
    ["p0002.lua"] = {get_answer(2), false},
    ["p0003.lua"] = {get_answer(3), false},
    ["p0004.lua"] = {get_answer(4), false},
    ["p0005.lua"] = {get_answer(5), false},
    ["p0006.lua"] = {get_answer(6), false},
    ["p0007.lua"] = {get_answer(7), false},
    ["p0008.lua"] = {get_answer(8), false},
    ["p0009.lua"] = {get_answer(9), false},
    ["p0010.lua"] = {get_answer(10), false},
    ["p0011.lua"] = {get_answer(11), false},
    ["p0013.lua"] = {get_answer(13), false},
    ["p0014.lua"] = {get_answer(14), false},
    ["p0015.lua"] = {get_answer(15), false},
    ["p0017.lua"] = {get_answer(17), false},
    ["p0028.lua"] = {get_answer(28), false},
    ["p0034.lua"] = {get_answer(34), false},
    ["p0076.lua"] = {get_answer(76), true},
    ["p0836.lua"] = {get_answer(836), false},
}

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
