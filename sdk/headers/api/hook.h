#pragma once
#include"lightbase.h"
#include<string>
extern "C" {
	// The core api of the hook function
		//__declspec(dllimport) int HookFunction(void* oldfunc, void** poutold, void* newfunc);
	// Used to get a server-defined specific function by name
	LBAPI int HookFunction(void* oldfunc, void** poutold, void* newfunc);
	LBAPI void* dlsym_real(char const* name);
	LBAPI void WaitForDebugger();
}
LBAPI std::string ptr2name(void* ptr);
LBAPI std::string GetDataPath(const std::string& myname);