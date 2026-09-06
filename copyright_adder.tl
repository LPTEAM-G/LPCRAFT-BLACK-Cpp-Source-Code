-- add_copyright.tl
-- 用途：为 src/ 目录下的 .cc/.c/.cpp/.h/.hpp 文件添加版权头

local function starts_with(s: string, prefix: string): boolean
	return s:sub(1, #prefix) == prefix
end

-- 处理单个文件：检查并添加版权
local function add_copyright_to_file(filename: string): boolean
	local f = io.open(filename, "r")
	if not f then
		return false
	end
	local content = f:read("*all")
	f:close()

	local copyright = "//Copyright (c) 2026 LPTEAM\n"

	-- 如果已经以版权行开头，则跳过
	if starts_with(content, copyright) then
		return true
	end

	-- 否则在前面插入版权行
	local new_content = copyright .. content
	local out = io.open(filename, "w")
	if not out then
		return false
	end
	out:write(new_content)
	out:close()
	return true
end

-- 使用 find 命令收集所有符合条件的文件路径
local function find_files(): {string}
	local files: {string} = {}
	local cmd = [[find src -type f \( -name "*.cc" -o -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \)]]
	local handle = io.popen(cmd)
	if not handle then
		return files
	end
	for line in handle:lines() do
		table.insert(files, line)
	end
	handle:close()
	return files
end

local function main()
	local files = find_files()
	if #files == 0 then
		print("No matching files found in src/")
		return
	end

	for _, file in ipairs(files) do
		local ok = add_copyright_to_file(file)
		if ok then
			print("[OK] " .. file)
		else
			print("[FAIL] " .. file)
		end
	end
end

main()
