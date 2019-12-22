#pragma once
#include <Windows.h>
#include <string>
#include "Memory.h"

class Menu;

class NoClip
{

public:

	Memory * memory;
	Menu * menu;

	bool noClipIsActive;
	bool vanillaMovementIsActive;
	bool showToggleDebugInfo = false;
	bool firstTimeToggled = true;

	int directionsPressed = 0;

	float playerX, playerY, playerZ = 0;
	float vectorX, vectorY, vectorZ = 0;
	float playerPitch, playerYaw = 0;
	float pi = 3.14f;
	float defaultElevation = 0;
	float newElevation = 10;
	float movementSpeed = 10;

	void ToggleNoClipMode();
	void CheckVanillaMovement();
	void MovePlayer(std::string direction);
};