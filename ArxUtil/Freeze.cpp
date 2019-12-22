#include <Windows.h>
#include "Freeze.h"

void Freeze::FreezeUnfreezeCreature()
{
	DWORD target;
	ReadProcessMemory(memory->handle, (LPVOID)memory->target, &target, sizeof(target), 0);

	if (target == '0x0')
	{
		return;
	}

	int entityID;
	ReadProcessMemory(memory->handle, (LPVOID)target, &entityID, sizeof(entityID), 0);

	if (std::find(creatureIDs.begin(), creatureIDs.end(), entityID) != creatureIDs.end())
	{
		// Entity is an unfrozen creature
		WriteProcessMemory(memory->handle, (LPVOID)target, &frozen, sizeof(frozen), 0);
	}

	if (entityID == frozen)
	{
		WriteProcessMemory(memory->handle, (LPVOID)target, &unfrozen, sizeof(unfrozen), 0);
	}

	Sleep(250);
}