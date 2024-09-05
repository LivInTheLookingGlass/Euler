-- Function to load a problem solution file
local function load_problem(file_name)
    local func, err = loadfile("src/" .. file_name)
    if not func then
        error("Failed to load file " .. file_name .. ": " .. err)
    end
    local chunk = func()
    if type(chunk) ~= "table" or not chunk.solution then
        error("File src/" .. file_name .. " must return a table with a 'solution' function")
    end
    return chunk.solution
end

-- Timing and result check function
local function check_problem(problem_func, expected_answer, timeout_seconds, problem_name)
    local start_time = os.clock()
    local success, result = pcall(problem_func)
    local elapsed_time = os.clock() - start_time

    if not success then
        error("Error executing " .. problem_name .. ": " .. result)
    end

    if result ~= expected_answer then
        error("Problem " .. problem_name .. " returned " .. tostring(result) .. ", but expected " .. tostring(expected_answer))
    end

    if elapsed_time > timeout_seconds then
        error("Problem " .. problem_name .. " took " .. tostring(elapsed_time) .. "s, exceeding the expected time limit of " .. tostring(timeout_seconds) .. "s.")
    end

    print("Problem " .. problem_name .. " passed.")
end

-- Problems configuration: filename -> {expected_answer, timeout_seconds}
local problems = {
    ["p0001.lua"] = {233168, 60},
    ["p0002.lua"] = {4613732, 60},
    -- Add more problems here as needed
}

-- Main testing loop
for file_name, config in pairs(problems) do
    local problem_func = load_problem(file_name)
    check_problem(problem_func, config[1], config[2], file_name:match("(%d+)"))
end
