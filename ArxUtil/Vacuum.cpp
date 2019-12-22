#include <iostream>
#include <string>
#include <vector>
#include "Vacuum.h"
#include "Menu.h"

void Vacuum::LocateEntityList()
{
	memory->pointerToEntityList = memory->moduleBaseAddress + memory->pointerToEntityList;
}

void Vacuum::CreateVacuum(std::string entityType)
{
	bool vacuuming = true;
	bool vacuumThisEntity = false;

	int currentEntityID = 0;
	int entityCounter = 1;
	int entitiesVacuumed = 0;
	std::vector<int> * comparisonType = nullptr;

	if (entityType == "item")
	{
		comparisonType = &itemIDs;
	}
	else if (entityType == "creature")
	{
		comparisonType = &creatureIDs;
	}
	else if (entityType == "container")
	{
		comparisonType = &containerIDs;
	}

	// Calculate starting address of entity list
	ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->pointerToEntityList),
		&memory->entityList, sizeof(memory->entityList), 0);

	while (vacuuming)
	{
		// Reset the validation flag
		vacuumThisEntity = false;

		// Stop vacuuming at the end of the entity list
		if (entityCounter >= entityListSize)
		{
			// Disabled until color change is fixed
			//menu->Update();
			return;
		}

		// Set the teleport destination to player position
		ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerXPosition), &playerX, sizeof(playerX), 0);
		ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerYPosition), &playerY, sizeof(playerY), 0);
		ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerZPosition), &playerZ, sizeof(playerZ), 0);

		// Get rotation of player for vacuum placement
		ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerYRotation), &playerYaw, sizeof(playerYaw), 0);

		// Convert rotational degrees to radians
		playerYaw = playerYaw * (pi / 180);

		// Calculate forward vector using rotations
		vectorX = -(cos(playerPitch) * sin(playerYaw));
		vectorZ = cos(playerPitch) * cos(playerYaw);

		// Apply distance offset to vector
		vectorX = vectorX * distanceOffset;
		vectorZ = vectorZ * distanceOffset;

		// Add vector to coordinates
		playerX += vectorX;
		playerZ += vectorZ;

		// Modify height so entities don't spawn at head height
		playerY += heightAdjust;

		// Move to next entity pointer
		memory->entityList += memory->entitySize;
		entityCounter++;

		// Read entity
		DWORD currentEntity;
		ReadProcessMemory(memory->handle, (LPVOID)memory->entityList, &currentEntity, sizeof(currentEntity), 0);

		// Make sure entity is the correct entity type before vacuuming
		ReadProcessMemory(memory->handle, (LPVOID)currentEntity, &currentEntityID, sizeof(currentEntityID), 0);
		
		if (std::find(comparisonType->begin(), comparisonType->end(), currentEntityID) != comparisonType->end())
		{
			// Entity meets criteria in comparisonType
			vacuumThisEntity = true;
		}
		
		//Vacuum this entity if it meets the criteria
		if (vacuumThisEntity)
		{
			// Grab visibility status and store it
			//ReadProcessMemory(memory->handle, (LPVOID)(currentEntity + memory->entityStatus), &entityVisible, sizeof(entityVisible), 0);
			//std::cout << entityVisible << ", ";

			// Write coordinates to entity
			WriteProcessMemory(memory->handle, (LPVOID)(currentEntity + memory->entityXPosition), &playerX, sizeof(playerX), 0);
			WriteProcessMemory(memory->handle, (LPVOID)(currentEntity + memory->entityYPosition), &playerY, sizeof(playerY), 0);
			WriteProcessMemory(memory->handle, (LPVOID)(currentEntity + memory->entityZPosition), &playerZ, sizeof(playerZ), 0);

			// Modify the entity status
			WriteProcessMemory(memory->handle, (LPVOID)(currentEntity + memory->entityStatus), &entityVisible, sizeof(entityVisible), 0);

			entitiesVacuumed++;
			//Sleep(50);
		}
	}
}