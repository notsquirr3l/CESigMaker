# CESigMaker

Developed to find patterns very quickly inside dll files

### Limitations

Sigs are always 18 bytes are not checked to be unique

### Example code to parse sig (C++)

```
uintptr_t find_pattern(const char* module, const unsigned char* pattern, size_t size, size_t offset, size_t extra) {
	uintptr_t address = 0;

	MODULEINFO miModInfo;
	K32GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(module), &miModInfo, sizeof(MODULEINFO));

	const auto mod_addr = reinterpret_cast<uintptr_t>(miModInfo.lpBaseOfDll);
	const auto mod_size = mod_addr + miModInfo.SizeOfImage;
	const auto mod_max = mod_addr + mod_size;

	unsigned char* sig = nullptr;

	MEMORY_BASIC_INFORMATION memory_basic_info = {};
	uintptr_t last_query = 0;
	uintptr_t curr_query = 1;

	for (auto i = mod_addr; i < mod_max; i++) {
		// check if sig size can fit in the module
		if (i + size < mod_max) {
			int c = 0;

			sig = read_bytes(i, size, false);

			// loop over copied sig and compare against searched sig
			for (auto k = 0; k < size; k++) {
				auto l = sig[k];

				if (pattern[k] == '\?' || pattern[k] == l)
					c++;
				else {
					delete[] sig;
					break;
				}
			}

			// if all is matched then correct sig, return the address
			if (c >= size - 1) {
				address = i + c - offset + extra;
				break;
			}

			continue;
		}

		break;
	}

	return address;
}

uintptr_t find_pattern(const char* module, const char* pattern, size_t size, size_t offset, size_t extra) {
	return find_pattern(module, reinterpret_cast<unsigned const char*>(pattern), size, offset, extra);
}
```

# Libraries used

* HDE
* CESDK
