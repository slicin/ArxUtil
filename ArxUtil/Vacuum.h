#pragma once
#include <string>
#include <vector>
#include "Memory.h"

class Menu;

class Vacuum
{

public:

	Memory * memory;
	Menu * menu;

	bool showVacuumDebugInfo = true;

	int entityVisible = 131071;
	int entityListSize = 1024;
	std::vector<int> itemIDs = { 4, 5, 36, 1028, 536870916 };
	std::vector<int> creatureIDs = { 8, 24, 26, 4104, 4616 };
	std::vector<int> containerIDs = { 16, 528 };

	float playerX, playerY, playerZ = 0;
	float playerPitch, playerYaw = 0;
	float vectorX, vectorY, vectorZ = 0;
	float heightAdjust = 150;
	float pi = 3.14f;
	float distanceOffset = 200;

	void LocateEntityList();
	void CreateVacuum(std::string entityType);
};