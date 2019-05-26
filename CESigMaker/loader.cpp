#include "loader.h"

static CE_EXPORTED_FUNCTIONS exports;

//static int memory_view_tab_pluginid = -1;

static CE_MEMORY_VIEW_PLUGIN_INIT memory_view_tab;
static CE_DISASSEMBLER_CONTEXT_INIT disassembler_context_option;

static size_t sig_size = 18;

void set_clipboard(const std::string& str) {
	OpenClipboard(0);
	EmptyClipboard();
	
	auto buf = GlobalAlloc(GMEM_MOVEABLE, str.size());
	
	if (!buf) {
		CloseClipboard();
		return;
	}

	std::memcpy(GlobalLock(buf), str.c_str(), str.size());
	
	GlobalUnlock(buf);
	SetClipboardData(CF_TEXT, buf);
	CloseClipboard();
	GlobalFree(buf);
}

BOOL CE_CONV on_makesig(uintptr_t* selected_address) {
	std::ostringstream stream;
	HDE hs;

	auto size = sig_size + 2;
	auto handle = *exports.OpenedProcessHandle;
	auto buffer = new unsigned char[size];

	std::memset(buffer, 0, sig_size);
	ReadProcessMemory(handle, reinterpret_cast<void*>(*selected_address - sig_size), buffer, size, nullptr);

	for (int i = 0; i < size; i++) {
		unsigned char c = buffer[i];
		HDE_DISASM(buffer + i, &hs);

		switch (hs.opcode) {
		case 0xE8: // call
		case 0xE9: // jmp
			i += hs.len;
			for (int k = 0; k < hs.len; k++)
				stream << "\\?";
			continue;
		}

		stream << "\\x" << std::hex << std::setfill('0') << std::setw(2) << std::uppercase << static_cast<int>(c);
	}

	delete[] buffer;

	auto str = stream.str();
	auto res = stream.str().substr(0, str.size() - 3);

	set_clipboard(res);

	exports.ShowMessage("Copied signature to clipboard!");

	return true;
}

BOOL CE_CONV on_rightclick(uintptr_t selected_address, const char** name_address, BOOL* show) {
	return true;
}

BOOL CE_CONV on_settings_click(uintptr_t* disassembler_address, uintptr_t* selected_disassembler_address, uintptr_t* hexview_address) {

	return TRUE;
}

BOOL CE_CONV CEPlugin_GetVersion(CE_PLUGIN_VERSION* version, int version_size) {
	version->plugin_name = "SigMaker";
	version->version = 1.0;

	return sizeof(CE_PLUGIN_VERSION) == version_size;
}

BOOL CE_CONV CEPlugin_InitializePlugin(CE_EXPORTED_FUNCTIONS* ef, int pluginid) {
	exports = *ef;

	memory_view_tab.name = "SigMaker: Settings";
	memory_view_tab.callback_routine = on_settings_click;
	memory_view_tab.shortcut = "Ctrl+E";

	disassembler_context_option.name = "SigMaker: Create signature";
	disassembler_context_option.callback_routine = &on_makesig;
	disassembler_context_option.callback_routine_onpopup = &on_rightclick;

	exports.RegisterFunction(pluginid, CE_PLUGIN_TYPE_DISASSEMBLER_CONTEXT, &disassembler_context_option);
	//memory_view_tab_pluginid = exports.RegisterFunction(pluginid, CE_PLUGIN_TYPE_MEMORY_VIEW, &memory_view_tab); //adds a plugin menu item to the memory view

	return true;
}

BOOL CE_CONV CEPlugin_DisablePlugin() {
	return true;
}