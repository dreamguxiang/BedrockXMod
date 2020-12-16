#pragma once
#include<string>
#include<api\lightbase.h>
namespace I18N {
	using std::string;
	extern LIGHTBASE_API string CMD_SUCCESS;
	extern LIGHTBASE_API string CMD_EXCEPTION;
	extern LIGHTBASE_API string EVENT_EXCEPTION_S;
	extern LIGHTBASE_API string S_TARGET;
	extern LIGHTBASE_API string S_OPERATION;
	void InitAll();
};