#include <Windows.h>
#include <cmath>
#include "Teleport.h"

void Teleport::TeleportToNearestEntity()
{
	bool lookingForNearestEntity = true;
	bool firstComparison = true;

	//int currentEntityID = 0;
	int entityCounter = 1;

	// Calculate starting address of entity list
	ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->pointerToEntityList),
		&memory->entityList, sizeof(memory->entityList), 0);

	// Get current player position
	ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerXPosition), &playerX, sizeof(playerX), 0);
	ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerYPosition), &playerY, sizeof(playerY), 0);
	ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerZPosition), &playerZ, sizeof(playerZ), 0);

	// Set destination to current position for fail safety
	destinationX = playerX;
	destinationY = playerY;
	destinationZ = playerZ;

	while (lookingForNearestEntity)
	{
		// Stop searching at the end of the entity list and teleport to nearest entity
		if (entityCounter >= entityListSize)
		{
			// Adjust Y position to avoid spawning underground
			destinationY -= heightAdjust;

			// Write destination to player position
			WriteProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerXPosition),
				&destinationX, sizeof(destinationX), 0);
			WriteProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerYPosition),
				&destinationY, sizeof(destinationY), 0);
			WriteProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerZPosition),
				&destinationZ, sizeof(destinationZ), 0);

			return;
		}

		// Move to next entity pointer
		memory->entityList += memory->entitySize;
		entityCounter++;

		// Read entity
		DWORD currentEntity;
		ReadProcessMemory(memory->handle, (LPVOID)memory->entityList, &currentEntity, sizeof(currentEntity), 0);

		// Read entity position
		ReadProcessMemory(memory->handle, (LPVOID)(currentEntity + memory->entityXPosition), &entityX, sizeof(entityX), 0);
		ReadProcessMemory(memory->handle, (LPVOID)(currentEntity + memory->entityYPosition), &entityY, sizeof(entityY), 0);
		ReadProcessMemory(memory->handle, (LPVOID)(currentEntity + memory->entityZPosition), &entityZ, sizeof(entityZ), 0);

		// Get distance between player and entity using following formula:
		// distance = sqrt[((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2)]
		currentDistance = sqrt((pow(entityX - playerX, 2)
			+ pow(entityY - playerY, 2)
			+ pow(entityZ - playerZ, 2)));

		// Change default destination to first entity
		if (firstComparison)
		{
			shortestDistance = currentDistance;
			destinationX = entityX;
			destinationY = entityY;
			destinationZ = entityZ;
			firstComparison = false;
		}

		// Update shortest distance if it's beaten
		if (currentDistance < shortestDistance)
		{
			shortestDistance = currentDistance;
			destinationX = entityX;
			destinationY = entityY;
			destinationZ = entityZ;
		}
	}
}