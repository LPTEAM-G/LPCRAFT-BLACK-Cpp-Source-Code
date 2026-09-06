-- replace_content.tl
-- Purpose: Recursively replace exact text in C/C++ source/header files under src/
-- Usage:   tl run replace_content.tl <search> <change>

-- Lua pattern escaping for literal string matching
local function escape_pattern(s: string): string
	return (s:gsub("[%^%$%(%)%%%.%[%]%*%+%-%?]", "%%%0"))
end

local function print_help()
	local help = [[
Usage: tl run replace_content.tl <search> <change>
       or lua replace_content.lua <search> <change>

Description:
	Recursively search all .cc/.c/.cpp/.h/.hpp files under src/
	and replace every occurrence of the exact string <search>
	with <change> (literal plain text, not a regex pattern).

Arguments:
	search    - the literal text to find
	change    - the literal text to replace with

Options:
	--help    - display this help message and exit

Examples:
	tl run replace_content.tl "old_function" "new_function"
	tl run replace_content.tl "std::endl" "std::flush"
	tl run replace_content.tl "Copyright 2025" "Copyright 2026"

Notes:
	- The replacement is performed in-place; original files are overwritten.
	- Use quotes to preserve spaces or special shell characters.
	- The script scans only files with extensions: .cc, .c, .cpp, .h, .hpp
]]
	print(help)
end

local function main()
	-- In Lua, arg[0] is the script name, arg[1]..arg[n] are the real arguments.
	-- #arg gives the count of arguments (excluding arg[0]).
	if #arg < 1 then
		print("Error: missing arguments.")
		print_help()
		return
	end

	if arg[1] == "--help" or arg[1] == "-h" then
		print_help()
		return
	end

	if #arg < 2 then
		print("Error: both <search> and <change> are required.")
		print_help()
		return
	end

	local search = arg[1]
	local change = arg[2]
	local pattern = escape_pattern(search)

	-- Collect all target files
	local cmd = [[find src -type f \( -name "*.cc" -o -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \)]]
	local handle = io.popen(cmd)
	if not handle then
		print("Failed to execute find command")
		return
	end

	local files: {string} = {}
	for line in handle:lines() do
		table.insert(files, line)
	end
	handle:close()

	if #files == 0 then
		print("No matching files found in src/")
		return
	end

	-- Process each file
	for _, filename in ipairs(files) do
		local f = io.open(filename, "r")
		if not f then
			print("[FAIL] Cannot read " .. filename)
			goto continue
		end

		local content = f:read("*all")
		f:close()

		local new_content, count = content:gsub(pattern, change)

		if count > 0 then
			local out = io.open(filename, "w")
			if not out then
				print("[FAIL] Cannot write " .. filename)
				goto continue
			end
			out:write(new_content)
			out:close()
			print("[OK] " .. filename .. " (" .. count .. " replacements)")
		else
			print("[SKIP] " .. filename .. " (no match)")
		end

		::continue::
	end
end

main()