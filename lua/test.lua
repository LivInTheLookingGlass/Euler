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
    local problem_func = load_problem("src/" .. file_name)
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

    if not is_slow and elapsed_time > 60 then
        error(
            "Problem " .. problem_name .. " took " .. tostring(elapsed_time) ..
            "s, exceeding the expected time limit of 60s."
        )
    end

    print("Problem " .. problem_name .. " passed.")
end

-- Problems configuration: filename -> {expected_answer, is_slow}
local problems = {
    ["p0001.lua"] = {233168, false},
    ["p0002.lua"] = {4613732, false},
    ["p0004.lua"] = {906609, false},
    ["p0006.lua"] = {25164150, false},
    ["p0009.lua"] = {31875000, false},
    ["p0017.lua"] = {21124, false},
    ["p0028.lua"] = {669171001, false},
    ["p0034.lua"] = {40730, false},
    ["p0836.lua"] = {"aprilfoolsjoke", false},
    ["p0076.lua"] = {190569291, true},
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
