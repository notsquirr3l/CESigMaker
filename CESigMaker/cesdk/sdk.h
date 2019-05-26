#ifndef _CESDK_SDK_H_
#define _CESDK_SDK_H_

#include "lib/lib.h"
#include "lua/lua.h"

#include <windows.h>

#define CESDK_VERSION 6

#define CE_CONV __stdcall

typedef enum _CE_PLUGIN_TYPE {
	CE_PLUGIN_TYPE_ADDRESS_LIST,
	CE_PLUGIN_TYPE_MEMORY_VIEW,
	CE_PLUGIN_TYPE_ON_DEBUG_EVENT,
	CE_PLUGIN_TYPE_PROCESS_WATCHER_EVENT,
	CE_PLUGIN_TYPE_FUNCTION_POINTER_CHANGE,
	CE_PLUGIN_TYPE_MAINMENU,
	CE_PLUGIN_TYPE_DISASSEMBLER_CONTEXT,
	CE_PLUGIN_TYPE_DISASSEMBLER_RENDERLINE,
	CE_PLUGIN_TYPE_AUTO_ASSEMBLER
} CE_PLUGIN_TYPE;

typedef enum _CE_AUTO_ASSEMBLER_PHASE {
	CE_AUTO_ASSEMBLER_PHASE_INITIALIZE,
	CE_AUTO_ASSEMBLER_PHASE_PHASE1,
	CE_AUTO_ASSEMBLER_PHASE_PHASE2,
	CE_AUTO_ASSEMBLER_PHASE_FINALIZE
} CE_AUTO_ASSEMBLER_PHASE;

typedef struct _CE_PLUGIN_VERSION {
	unsigned int version;
	const char* plugin_name;
} CE_PLUGIN_VERSION;

typedef struct _CE_ADDRESS_LIST_RECORD {
	const char interpreted_address[255];
	uintptr_t address;
	BOOL is_pointer;
	int offset_counts;
	unsigned long* offsets;
	const char* description;
	char valuetype;
	char size;
} CE_ADDRESS_LIST_RECORD;

typedef BOOL(__stdcall* CEP_PLUGIN_TYPE_0)(CE_ADDRESS_LIST_RECORD* selected_record);
typedef BOOL(__stdcall* CEP_PLUGIN_TYPE_1)(uintptr_t* disassembler_address, uintptr_t* selected_disassembler_address, uintptr_t* hexview_address);
typedef BOOL(__stdcall* CEP_PLUGIN_TYPE_2)(DEBUG_EVENT* debug_event);
typedef BOOL(__stdcall* CEP_PLUGIN_TYPE_3)(unsigned long pid, unsigned long peprocess, BOOL created);
typedef BOOL(__stdcall* CEP_PLUGIN_TYPE_4)(int reserved);
typedef BOOL(__stdcall* CEP_PLUGIN_TYPE_5)();
typedef BOOL(__stdcall* CEP_PLUGIN_TYPE_6)(uintptr_t* selected_address);

typedef BOOL(__stdcall* CEP_PLUGIN_TYPE_6_ONPOPUP)(uintptr_t selected_address, const char** name_address, BOOL* show);

typedef BOOL(__stdcall* CEP_PLUGIN_TYPE_7)(uintptr_t address, const char** address_string_pointer, const unsigned char** byte_string_pointer, const char** opcode_string_pointer, const char** special_string_pointer, unsigned long* textcolor);
typedef BOOL(__stdcall* CEP_PLUGIN_TYPE_8)(const char** line, CE_AUTO_ASSEMBLER_PHASE phase, int id);

typedef struct _CE_PLUGIN_TYPE_0_INIT {
	const char* name;
	CEP_PLUGIN_TYPE_0 callback_routine;
} CE_PLUGIN_TYPE_0_INIT, CE_ADDRESS_LIST_PLUGIN_INIT;

typedef struct _CE_PLUGIN_TYPE_1_INIT {
	const char* name;
	CEP_PLUGIN_TYPE_1 callback_routine;
	const char* shortcut;
} CE_PLUGIN_TYPE_1_INIT, CE_MEMORY_VIEW_PLUGIN_INIT;

typedef struct _CE_PLUGIN_TYPE_2_INIT {
	CEP_PLUGIN_TYPE_2 callback_routine;
} CE_PLUGIN_TYPE_2_INIT, CE_DEBUG_EVENT_PLUGIN_INIT;

typedef struct _CE_PLUGIN_TYPE_3_INIT {
	CEP_PLUGIN_TYPE_3 callback_routine;
} CE_PLUGIN_TYPE_3_INIT, CE_PROCESS_WATCHER_PLUGIN_INIT;

typedef struct _CE_PLUGIN_TYPE_4_INIT {
	CEP_PLUGIN_TYPE_4 callback_routine;
} CE_PLUGIN_TYPE_4_INIT, CE_POINTER_REASSIGNMENT_PLUGIN_INIT;

typedef struct _CE_PLUGIN_TYPE_5_INIT {
	const char* name;
	CEP_PLUGIN_TYPE_5 callback_routine;
	const char* shortcut;
} CE_PLUGIN_TYPE_5_INIT, CE_MAIN_MENU_PLUGIN_INIT;

typedef struct _CE_PLUGIN_TYPE_6_INIT {
	const char* name;
	CEP_PLUGIN_TYPE_6 callback_routine;
	CEP_PLUGIN_TYPE_6_ONPOPUP callback_routine_onpopup;
	const char* shortcut;
} CE_PLUGIN_TYPE_6_INIT, CE_DISASSEMBLER_CONTEXT_INIT;

typedef struct _CE_PLUGIN_TYPE_7_INIT {
	CEP_PLUGIN_TYPE_7 callback_routine;
} CE_PLUGIN_TYPE_7_INIT, CE_DISASSEMBLER_LINE_PLUGIN_INIT;

typedef struct _CE_PLUGIN_TYPE_8_INIT {
	CEP_PLUGIN_TYPE_8 callback_routine;
} CE_PLUGIN_TYPE_8_INIT, CE_AUTOASSEMBLER_PLUGIN_INIT;

#ifdef _WIN32 || _WIN64

#ifndef _WIN64

typedef struct _CE_REGISTER_MODIFICATION_INFO {
	unsigned int* address;
	BOOL change_eax;
	BOOL change_ebx;
	BOOL change_ecx;
	BOOL change_edx;
	BOOL change_esi;
	BOOL change_edi;
	BOOL change_ebp;
	BOOL change_esp;
	BOOL change_eip;
	BOOL change_cf;
	BOOL change_pf;
	BOOL change_af;
	BOOL change_zf;
	BOOL change_sf;
	BOOL change_of;

	uintptr_t new_eax;
	uintptr_t new_ebx;
	uintptr_t new_ecx;
	uintptr_t new_edx;
	uintptr_t new_esi;
	uintptr_t new_edi;
	uintptr_t new_ebp;
	uintptr_t new_esp;
	uintptr_t new_eip;

	BOOL new_cf;
	BOOL new_pf;
	BOOL new_af;
	BOOL new_zf;
	BOOL new_sf;
	BOOL new_of;
} CE_REGISTER_MODIFICATION_INFO;

#else

typedef struct _CE_REGISTER_MODIFICATION_INFO {
	unsigned int* address;
	BOOL change_eax;
	BOOL change_ebx;
	BOOL change_ecx;
	BOOL change_edx;
	BOOL change_esi;
	BOOL change_edi;
	BOOL change_ebp;
	BOOL change_esp;
	BOOL change_eip;
	BOOL change_r8;
	BOOL change_r9;
	BOOL change_10;
	BOOL change_11;
	BOOL change_12;
	BOOL change_13;
	BOOL change_14;
	BOOL change_15;
	BOOL change_cf;
	BOOL change_pf;
	BOOL change_af;
	BOOL change_zf;
	BOOL change_sf;
	BOOL change_of;

	uintptr_t new_eax;
	uintptr_t new_ebx;
	uintptr_t new_ecx;
	uintptr_t new_edx;
	uintptr_t new_esi;
	uintptr_t new_edi;
	uintptr_t new_ebp;
	uintptr_t new_esp;
	uintptr_t new_eip;
	uintptr_t new_r8;
	uintptr_t new_r9;
	uintptr_t new_r10;
	uintptr_t new_r11;
	uintptr_t new_r12;
	uintptr_t new_r13;
	uintptr_t new_r14;
	uintptr_t new_r15;

	BOOL new_cf;
	BOOL new_pf;
	BOOL new_af;
	BOOL new_zf;
	BOOL new_sf;
	BOOL new_of;
} CE_REGISTER_MODIFICATION_INFO;

#endif

#elif

#error "ARCHITECHTURE IS NOT SUPPORTED!"

#endif

typedef void(__stdcall* CEP_SHOWMESSAGE)(const char* message);
typedef int(__stdcall* CEP_REGISTERFUNCTION)(int pluginid, CE_PLUGIN_TYPE functiontype, void* init);
typedef BOOL(__stdcall* CEP_UNREGISTERFUNCTION)(int pluginid, int functionid);
typedef HANDLE(__stdcall* CEP_GETMAINWINDOWHANDLE)();
typedef BOOL(__stdcall* CEP_AUTOASSEMBLE)(const char* script);
typedef BOOL(__stdcall* CEP_ASSEMBLER)(uintptr_t address, const char* instruction, BYTE* output, int maxlength, int* returnedsize);
typedef BOOL(__stdcall* CEP_DISASSEMBLER)(uintptr_t address, const char* output, int maxsize);
typedef BOOL(__stdcall* CEP_CHANGEREGATADDRESS)(uintptr_t address, CE_REGISTER_MODIFICATION_INFO* changereg);
typedef BOOL(__stdcall* CEP_INJECTDLL)(const char* dllname, const char* functiontocall);
typedef int(__stdcall* CEP_FREEZEMEM)(uintptr_t address, int size);
typedef BOOL(__stdcall* CEP_UNFREEZEMEM)(int freezeID);
typedef BOOL(__stdcall* CEP_FIXMEM)();
typedef BOOL(__stdcall* CEP_PROCESSLIST)(const char* listbuffer, int listsize);
typedef BOOL(__stdcall* CEP_RELOADSETTINGS)();
typedef DWORD(__stdcall* CEP_GETADDRESSFROMPOINTER)(uintptr_t baseaddress, int offsetcount, int* offsets);
typedef BOOL(__stdcall* CEP_GENERATEAPIHOOKSCRIPT)(const char* address, const char* addresstojumpto, const char* addresstogetnewcalladdress, const char* script, int maxscriptsize);
typedef BOOL(__stdcall* CEP_ADDRESSTONAME)(uintptr_t address, const char* name, int maxnamesize);
typedef BOOL(__stdcall* CEP_NAMETOADDRESS)(const const char* name, uintptr_t* address);

typedef void(__stdcall* CEP_LOADDBK32)();
typedef BOOL(__stdcall* CEP_LOADDBVMIFNEEDED)();
typedef DWORD(__stdcall* CEP_PREVIOUSOPCODE)(uintptr_t address);
typedef DWORD(__stdcall* CEP_NEXTOPCODE)(uintptr_t address);
typedef BOOL(__stdcall* CEP_LOADMODULE)(const char* modulepath, const char* exportlist, int* maxsize);
typedef BOOL(__stdcall* CEP_DISASSEMBLEEX)(uintptr_t address, const char* output, int maxsize);
typedef void(__stdcall* CEP_AA_ADDCOMMAND)(const char* command);
typedef void(__stdcall* CEP_AA_DELCOMMAND)(const char* command);

typedef void* (__stdcall* CEP_CREATETABLEENTRY)();
typedef void* (__stdcall* CEP_GETTABLEENTRY)(const char* description);
typedef BOOL(__stdcall* CEP_MEMREC_SETDESCRIPTION)(void* memrec, const char* description);
typedef PCHAR(__stdcall* CEP_MEMREC_GETDESCRIPTION)(void* memrec);
typedef BOOL(__stdcall* CEP_MEMREC_GETADDRESS)(void* memrec, uintptr_t* address, DWORD* offsets, int maxoffsets, int* neededOffsets);
typedef BOOL(__stdcall* CEP_MEMREC_SETADDRESS)(void* memrec, const char* address, DWORD* offsets, int offsetcount);
typedef int(__stdcall* CEP_MEMREC_GETTYPE)(void* memrec);
typedef BOOL(__stdcall* CEP_MEMREC_SETTYPE)(void* memrec, int vtype);
typedef BOOL(__stdcall* CEP_MEMREC_GETVALUETYPE)(void* memrec, const char* value, int maxsize);
typedef BOOL(__stdcall* CEP_MEMREC_SETVALUETYPE)(void* memrec, const char* value);
typedef char* (__stdcall* CEP_MEMREC_GETSCRIPT)(void* memrec);
typedef BOOL(__stdcall* CEP_MEMREC_SETSCRIPT)(void* memrec, const char* script);
typedef BOOL(__stdcall* CEP_MEMREC_ISFROZEN)(void* memrec);
typedef BOOL(__stdcall* CEP_MEMREC_FREEZE)(void* memrec, int direction);
typedef BOOL(__stdcall* CEP_MEMREC_UNFREEZE)(void* memrec);
typedef BOOL(__stdcall* CEP_MEMREC_SETCOLOR)(void* memrec, DWORD color);
typedef BOOL(__stdcall* CEP_MEMREC_APPENDTOENTRY)(void* memrec1, void* memrec2);
typedef BOOL(__stdcall* CEP_MEMREC_DELETE)(void* memrec);

typedef DWORD(__stdcall* CEP_GETPROCESSIDFROMPROCESSNAME)(const char* name);
typedef DWORD(__stdcall* CEP_OPENPROCESS)(DWORD pid);
typedef DWORD(__stdcall* CEP_DEBUGPROCESS)(int debuggerinterface);
typedef void(__stdcall* CEP_PAUSE)();
typedef void(__stdcall* CEP_UNPAUSE)();
typedef BOOL(__stdcall* CEP_DEBUG_SETBREAKPOINT)(uintptr_t address, int size, int trigger);
typedef BOOL(__stdcall* CEP_DEBUG_REMOVEBREAKPOINT)(uintptr_t address);
typedef BOOL(__stdcall* CEP_DEBUG_CONTINUEFROMBREAKPOINT)(int continueoption);

typedef void(__stdcall* CEP_CLOSECE)();
typedef void(__stdcall* CEP_HIDEALLCEWINDOWS)();
typedef void(__stdcall* CEP_UNHIDEMAINCEWINDOW)();

typedef void* (__stdcall* CEP_CREATEFORM)();
typedef void(__stdcall* CEP_FORM_CENTERSCREEN)(void* form);
typedef void(__stdcall* CEP_FORM_HIDE)(void* form);
typedef void(__stdcall* CEP_FORM_SHOW)(void* form);
typedef void(__stdcall* CEP_FORM_ONCLOSE)(void* form, void* function);

typedef void* (__stdcall* CEP_CREATEPANEL)(void* owner);
typedef void* (__stdcall* CEP_CREATEGROUPBOX)(void* owner);
typedef void* (__stdcall* CEP_CREATEBUTTON)(void* owner);
typedef void* (__stdcall* CEP_CREATEIMAGE)(void* owner);

typedef BOOL(__stdcall* CEP_IMAGE_LOADIMAGEFROMFILE)(void* image, char* filename);
typedef void(__stdcall* CEP_IMAGE_TRANSPARENT)(void* image, BOOL transparent);
typedef void(__stdcall* CEP_IMAGE_STRETCH)(void* image, BOOL stretch);

typedef void* (__stdcall* CEP_CREATELABEL)(void* owner);
typedef void* (__stdcall* CEP_CREATEEDIT)(void* owner);
typedef void* (__stdcall* CEP_CREATEMEMO)(void* owner);
typedef void* (__stdcall* CEP_CREATETIMER)(void* owner);

typedef void(__stdcall* CEP_TIMER_SETINTERVAL)(void* timer, int interval);
typedef void(__stdcall* CEP_TIMER_ONTIMER)(void* timer, void* function);

typedef void(__stdcall* CEP_CONTROL_SETCAPTION)(void* control, char* caption);
typedef BOOL(__stdcall* CEP_CONTROL_GETCAPTION)(void* control, char* caption, int maxsize);

typedef void(__stdcall* CEP_CONTROL_SETPOSITION)(void* control, int x, int y);
typedef int(__stdcall* CEP_CONTROL_GETX)(void* control);
typedef int(__stdcall* CEP_CONTROL_GETY)(void* control);

typedef void(__stdcall* CEP_CONTROL_SETSIZE)(void* control, int width, int height);
typedef int(__stdcall* CEP_CONTROL_GETWIDTH)(void* control);
typedef int(__stdcall* CEP_CONTROL_GETHEIGHT)(void* control);

typedef void(__stdcall* CEP_CONTROL_SETALIGN)(void* control, int align);
typedef void(__stdcall* CEP_CONTROL_ONCLICK)(void* control, void* function);

typedef void(__stdcall* CEP_OBJECT_DESTROY)(void* object);

typedef int(__stdcall* CEP_MESSAGEDIALOG)(char* massage, int messagetype, int buttoncombination);
typedef BOOL(__stdcall* CEP_SPEEDHACK_SETSPEED)(float speed);

typedef void* (__stdcall* CEP_GETLUASTATE)();

typedef void(__stdcall* CEP_PLUGINFUNC)(LPVOID parameters);
typedef void* (__stdcall* CEP_MAINTHREADCALL)(CEP_PLUGINFUNC func, LPVOID paramters);

typedef struct _CE_EXPORTED_FUNCTIONS {
	int sizeofExportedFunctions;
	CEP_SHOWMESSAGE ShowMessage; //Pointer to the ce showmessage function
	CEP_REGISTERFUNCTION RegisterFunction; //Use this to register a specific type of plugin
	CEP_UNREGISTERFUNCTION UnregisterFunction; //unregisters a function registered with registerfunction
	PULONG OpenedProcessID; //pointer to the currently selected processid
	PHANDLE OpenedProcessHandle; //pointer to the currently selected processhandle

	CEP_GETMAINWINDOWHANDLE GetMainWindowHandle; //returns the handle of the main window (for whatever reason, it is recommended to use delphi to make a real userinterface upgrade)
	CEP_AUTOASSEMBLE AutoAssemble; //Pointer to the AutoAssemble function
	CEP_ASSEMBLER Assembler; //pointer to the assembler function
	CEP_DISASSEMBLER Disassembler; //pointer to the disassembler function
	CEP_CHANGEREGATADDRESS ChangeRegistersAtAddress; //pointer to the ChangeRegAtBP function
	CEP_INJECTDLL InjectDLL; //pointer to ce's Inject DLL function
	CEP_FREEZEMEM FreezeMem; //pointer to the FreezeMem routine
	CEP_UNFREEZEMEM UnfreezeMem; //pointer to the UnfreezeMem routine (use this to undo freezes with FreezeMem)
	CEP_FIXMEM FixMem; //pointer to the fixmem routine
	CEP_PROCESSLIST ProcessList; //pointer to the processlist routine
	CEP_RELOADSETTINGS ReloadSettings; //pointer to the ReloadSettings routine
	CEP_GETADDRESSFROMPOINTER GetAddressFromPointer; //pointer to the GetAddressFromPointer routine

	//pointers to the address that contains the pointers to the functions
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	PVOID ReadProcessMemory;			//	pointer to the pointer of ReadProcessMemory (Change it to hook that api, or use it yourself)
	PVOID WriteProcessMemory;			//	pointer to the pointer of WriteProcessMemory (Change it to hook that api, or use it yourself)
	PVOID GetThreadContext;				//   ...
	PVOID SetThreadContext;				//   ...
	PVOID SuspendThread;				//   ...
	PVOID ResumeThread;					//   ...
	PVOID OpenProcess;					//   ...
	PVOID WaitForDebugEvent;			//   ...
	PVOID ContinueDebugEvent;			//   ...
	PVOID DebugActiveProcess;			//   ...
	PVOID StopDebugging;				//   ...
	PVOID StopRegisterChange;			//   ...
	PVOID VirtualProtect;				//   ...
	PVOID VirtualProtectEx;				//   ...
	PVOID VirtualQueryEx;				//   ...
	PVOID VirtualAllocEx;				//   ...
	PVOID CreateRemoteThread;			//   ...
	PVOID OpenThread;					//   ...
	PVOID GetPEProcess;					//   ...
	PVOID GetPEThread;					//   ...
	PVOID GetThreadsProcessOffset;		//   ...
	PVOID GetThreadListEntryOffset;		//   ...
	PVOID GetProcessnameOffset;			//   ...
	PVOID GetDebugportOffset;			//   ...
	PVOID GetPhysicalAddress;			//   ...
	PVOID ProtectMe;					//   ...
	PVOID GetCR4;						//   ...
	PVOID GetCR3;						//   ...
	PVOID SetCR3;						//   ...
	PVOID GetSDT;						//   ...
	PVOID GetSDTShadow;					//   ...
	PVOID setAlternateDebugMethod;		//   ...
	PVOID getAlternateDebugMethod;		//   ...
	PVOID DebugProcess;					//   ...
	PVOID ChangeRegOnBP;				//   ...
	PVOID RetrieveDebugData;			//   ...
	PVOID StartProcessWatch;			//   ...
	PVOID WaitForProcessListData;		//   ...
	PVOID GetProcessNameFromID;			//   ...
	PVOID GetProcessNameFromPEProcess;	//   ...
	PVOID KernelOpenProcess;			//   ...
	PVOID KernelReadProcessMemory;		//   ...
	PVOID KernelWriteProcessMemory;		//   ...
	PVOID KernelVirtualAllocEx;			//   ...
	PVOID IsValidHandle;				//   ...
	PVOID GetIDTCurrentThread;			//   ...
	PVOID GetIDTs;						//   ...
	PVOID MakeWritable;					//   ...
	PVOID GetLoadedState;				//   ...
	PVOID DBKSuspendThread;				//   ...
	PVOID DBKResumeThread;				//   ...
	PVOID DBKSuspendProcess;			//   ...
	PVOID DBKResumeProcess;				//   ...
	PVOID KernelAlloc;					//   ...
	PVOID GetKProcAddress;				//   ...
	PVOID CreateToolhelp32Snapshot;		//   ...
	PVOID Process32First;          		//   ...
	PVOID Process32Next;           		//   ...
	PVOID Thread32First;				//   ...
	PVOID Thread32Next;					//   ...
	PVOID Module32First;           		//   ...
	PVOID Module32Next;            		//   ...
	PVOID Heap32ListFirst;				//   ...
	PVOID Heap32ListNext;          		//   ...
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	//advanced for delphi 7 enterprise dll programmers only
	PVOID mainform;	//pointer to the Tmainform object. (main window) Compatible with TFORM of D7 Enterprise
	PVOID memorybrowser; //pointer to the TMemoryBrowser object (memory view windows), same as mainform

	//Plugin Version 2+
	CEP_NAMETOADDRESS sym_nameToAddress;
	CEP_ADDRESSTONAME sym_addressToName;
	CEP_GENERATEAPIHOOKSCRIPT sym_generateAPIHookScript;

	//Plugin version 3+
	CEP_LOADDBK32 loadDBK32;
	CEP_LOADDBVMIFNEEDED loaddbvmifneeded;
	CEP_PREVIOUSOPCODE previousOpcode;
	CEP_NEXTOPCODE nextOpcode;
	CEP_DISASSEMBLEEX disassembleEx;
	CEP_LOADMODULE loadModule;
	CEP_AA_ADDCOMMAND aa_AddExtraCommand;
	CEP_AA_DELCOMMAND aa_RemoveExtraCommand;

	//version 4 extension
	CEP_CREATETABLEENTRY createTableEntry;
	CEP_GETTABLEENTRY getTableEntry;
	CEP_MEMREC_SETDESCRIPTION memrec_setDescription;
	CEP_MEMREC_GETDESCRIPTION memrec_getDescription;
	CEP_MEMREC_GETADDRESS memrec_getAddress;
	CEP_MEMREC_SETADDRESS memrec_setAddress;
	CEP_MEMREC_GETTYPE memrec_getType;
	CEP_MEMREC_SETTYPE memrec_setType;
	CEP_MEMREC_GETVALUETYPE memrec_getValue;
	CEP_MEMREC_SETVALUETYPE memrec_setValue;
	CEP_MEMREC_GETSCRIPT memrec_getScript;
	CEP_MEMREC_SETSCRIPT memrec_setScript;
	CEP_MEMREC_ISFROZEN memrec_isfrozen;
	CEP_MEMREC_FREEZE memrec_freeze;
	CEP_MEMREC_UNFREEZE memrec_unfreeze;
	CEP_MEMREC_SETCOLOR memrec_setColor;
	CEP_MEMREC_APPENDTOENTRY memrec_appendtoentry;
	CEP_MEMREC_DELETE memrec_delete;

	CEP_GETPROCESSIDFROMPROCESSNAME getProcessIDFromProcessName;
	CEP_OPENPROCESS openProcessEx;
	CEP_DEBUGPROCESS debugProcessEx;
	CEP_PAUSE pause;
	CEP_UNPAUSE unpause;

	CEP_DEBUG_SETBREAKPOINT debug_setBreakpoint;
	CEP_DEBUG_REMOVEBREAKPOINT debug_removeBreakpoint;
	CEP_DEBUG_CONTINUEFROMBREAKPOINT debug_continueFromBreakpoint;

	CEP_CLOSECE closeCE;
	CEP_HIDEALLCEWINDOWS hideAllCEWindows;
	CEP_UNHIDEMAINCEWINDOW unhideMainCEwindow;
	CEP_CREATEFORM createForm;
	CEP_FORM_CENTERSCREEN form_centerScreen;
	CEP_FORM_HIDE form_hide;
	CEP_FORM_SHOW form_show;
	CEP_FORM_ONCLOSE form_onClose;

	CEP_CREATEPANEL createPanel;
	CEP_CREATEGROUPBOX createGroupBox;
	CEP_CREATEBUTTON createButton;
	CEP_CREATEIMAGE createImage;
	CEP_IMAGE_LOADIMAGEFROMFILE image_loadImageFromFile;
	CEP_IMAGE_TRANSPARENT image_transparent;
	CEP_IMAGE_STRETCH image_stretch;

	CEP_CREATELABEL createLabel;
	CEP_CREATEEDIT createEdit;
	CEP_CREATEMEMO createMemo;
	CEP_CREATETIMER createTimer;
	CEP_TIMER_SETINTERVAL timer_setInterval;
	CEP_TIMER_ONTIMER timer_onTimer;
	CEP_CONTROL_SETCAPTION control_setCaption;
	CEP_CONTROL_GETCAPTION control_getCaption;
	CEP_CONTROL_SETPOSITION control_setPosition;
	CEP_CONTROL_GETX control_getX;
	CEP_CONTROL_GETY control_getY;
	CEP_CONTROL_SETSIZE control_setSize;
	CEP_CONTROL_GETWIDTH control_getWidth;
	CEP_CONTROL_GETHEIGHT control_getHeight;
	CEP_CONTROL_SETALIGN control_setAlign;
	CEP_CONTROL_ONCLICK control_onClick;

	CEP_OBJECT_DESTROY object_destroy;
	CEP_MESSAGEDIALOG messageDialog;
	CEP_SPEEDHACK_SETSPEED speedhack_setSpeed;

	//V5: Todo, implement function declarations
	void* ExecuteKernelCode;
	void* UserdefinedInterruptHook;
	CEP_GETLUASTATE GetLuaState;
	CEP_MAINTHREADCALL MainThreadCall;
} CE_EXPORTED_FUNCTIONS;

#endif