#include <Windows.h>
#include <TlHelp32.h>
#include "ProcessUtility.h"

void ProcessUtility::Initialize()
{
	GetWindowHandle();
	GetProcessID();
	GetProcessHandle();
	GetModuleBaseAddress();
}

void ProcessUtility::GetWindowHandle()
{
	handleWindow = FindWindowA(0, processName);
}

void ProcessUtility::GetProcessID()
{
	GetWindowThreadProcessId(handleWindow, &processID);
}

void ProcessUtility::GetProcessHandle()
{
	memory->handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
}

void ProcessUtility::GetModuleBaseAddress()
{
	DWORD_PTR moduleBaseAddress = 0;
	HANDLE handleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
	if (handleSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ModuleEntry32;
		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(handleSnapshot, &ModuleEntry32))
		{
			do
			{
				if (strcmp(ModuleEntry32.szModule, moduleName) == 0)
				{
					moduleBaseAddress = (DWORD_PTR)ModuleEntry32.modBaseAddr;
					break;
				}
			} while (Module32Next(handleSnapshot, &ModuleEntry32));
		}
		CloseHandle(handleSnapshot);
	}

	memory->moduleBaseAddress = moduleBaseAddress;
}