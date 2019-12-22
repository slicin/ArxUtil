#pragma once
#include <Windows.h>
#include "Memory.h"
#include "NoClip.h"

class ProcessUtility
{

public:

	Memory * memory;
	NoClip * noClip;

	LPCSTR processName;
	HWND handleWindow;
	DWORD processID;
	char moduleName[8] = "arx.exe";

	void Initialize();
	void GetWindowHandle();
	void GetProcessID();
	void GetProcessHandle();
	void GetModuleBaseAddress();
};