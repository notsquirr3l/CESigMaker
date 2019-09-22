#ifndef _LOADER_H_
#define _LOADER_H_

#include <Windows.h>

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

#include "cesdk/sdk.h"

#if defined(_M_X64) || defined(__x86_64__)
#include "./hde/hde64.h"
typedef hde64s HDE;
#define HDE_DISASM(code, hs) hde64_disasm(code, hs)
#else
#include "./hde/hde32.h"
typedef hde32s HDE;
#define HDE_DISASM(code, hs) hde32_disasm(code, hs)
#endif

#define dllexport extern "C" __declspec(dllexport)

dllexport BOOL CE_CONV CEPlugin_GetVersion(CE_PLUGIN_VERSION* version, int version_size);
dllexport BOOL CE_CONV CEPlugin_InitializePlugin(CE_EXPORTED_FUNCTIONS* exports, int pluginid);
dllexport BOOL CE_CONV CEPlugin_DisablePlugin();

#endif