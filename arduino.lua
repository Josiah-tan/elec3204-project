local port = 5
local terminal = 1
local compile = function() -- compiles arduino code
	vim.fn.execute(":wa")
	string = "arduino-cli compile -b arduino:avr:uno -v"
	require("harpoon.term").sendCommand(terminal, string .. "\n")
end
local upload = function(port) -- uploads arduino code
	vim.fn.execute(":wa")
	string = "arduino-cli upload -p /dev/ttyS"..port.." -b arduino:avr:uno -v"
	require("harpoon.term").sendCommand(terminal, string .. "\n")
end
local compile_upload = function(port) -- compiles and uploads arduino code
	vim.fn.execute(":wa")
	string = "arduino-cli compile -u -p /dev/ttyS"..port.." -b arduino:avr:uno -v"
	require("harpoon.term").sendCommand(terminal, string .. "\n")
end
local function monitor_log() -- setup for running tail -f in nvim for monitor_log.txt
	return {
		file_name = "monitor_log.txt",
		viewer = {
			choose = "terminal",
			terminal = {
				number = 8
			}
		},
		split = {
			choose = "vertical"
		},
	}
end
local function write_log()
	return {
		file_name = "write_log.txt",
		viewer = {
			choose = "terminal",
			terminal = {
				number = 9
			}
		},
		split = {
			choose = "horizontal"
		},
	}
end

vim.keymap.set('n', '<leader>al', function ()  -- setup GUI for monitor and write log
	RELOAD("plover_viewer.builtin").splitToggle(monitor_log())
	vim.cmd[[wincmd p]]
	RELOAD("plover_viewer.builtin").splitToggle(write_log())
	vim.cmd[[wincmd h]]
end)

-- setup key bindings for compilation, upload and the combination of the two
vim.keymap.set({"n"}, "<leader>ac", function ()
	compile()
end, {silent = false})
vim.keymap.set({"n"}, "<leader>au", function ()
	upload(port)
end, {silent = false})
vim.keymap.set({"n"}, "<leader>ar", function ()
	compile_upload(port)
end, {silent = false})

-- the fuzzy finder option selector gui

-- function to get the selection from the GUI
local function getSelection(prompt_bufnr)
	local content = require("telescope.actions.state").get_selected_entry(
	prompt_bufnr
	)
	local current_line = require("telescope.actions.state").get_current_line()
	require("telescope.actions").close(prompt_bufnr)
	if content then
		content = content.value
	else
		content = current_line
	end
	return content
end

-- function to get the selection from the GUI and also send the selection to the terminal for execution
local function selectCommand(prompt_bufnr)
	local selection = getSelection(prompt_bufnr)
	require("harpoon.term").sendCommand(terminal, selection.."\n")
end


-- member function GUI: utilizes telescope API to create a new custom finder for command selection
M.gui = function(opts)
		opts = vim.tbl_deep_extend("force", {
			commands = {"pause", "normal", "quick", "stop", "gentle", "test", "terminate"}
		}, opts or {})
		require("telescope.pickers").new(opts, {
			prompt_title = "choose command > ",
			finder = require("telescope.finders").new_table({
				results = opts.commands
			}),
			sorter = require("telescope.config").values.generic_sorter(opts),
			attach_mappings = function(_, map)
				map("i", "<CR>", selectCommand)
				map("n", "<CR>", selectCommand)
				return true
			end
		}):find()
	end

-- key map for invoking the GUI
vim.api.nvim_set_keymap("n", "<Leader>gui", ':lua RELOAD("josiah.arduino").gui()<CR>', {noremap = true, silent = true, expr = false})

return M
