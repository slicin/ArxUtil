#pragma once
#include "Memory.h"

class Teleport
{

public:

	Memory * memory;

	int entityListSize = 1024;

	float currentDistance, shortestDistance = 0;
	float playerX, playerY, playerZ = 0;
	float entityX, entityY, entityZ = 0;
	float destinationX, destinationY, destinationZ = 0;
	float heightAdjust = 150;

	void TeleportToNearestEntity();
};