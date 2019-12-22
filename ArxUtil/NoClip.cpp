#include <Windows.h>
#include <string>
#include <iostream>
#include "Memory.h"
#include "NoClip.h"
#include "Menu.h"

void NoClip::ToggleNoClipMode()
{
	if (firstTimeToggled)
	{
		CheckVanillaMovement();
		firstTimeToggled = false;
	}

	vanillaMovementIsActive = !vanillaMovementIsActive;
	noClipIsActive = !vanillaMovementIsActive;

	menu->Update();

	if (showToggleDebugInfo)
	{
		std::cout << "\nvanillaMovementIsActive: " << vanillaMovementIsActive
			<< "\nnoClipIsActive: " << noClipIsActive;
	}

	if (vanillaMovementIsActive)
	{
		WriteProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->movementInstructions),
			&memory->vanillaMovement, sizeof(memory->vanillaMovement), 0);
		WriteProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerElevation),
			&defaultElevation, sizeof(defaultElevation), 0);
	}
	else
	{
		WriteProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->movementInstructions),
			&memory->disabledMovement, sizeof(memory->disabledMovement), 0);
		WriteProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerElevation),
			&newElevation, sizeof(newElevation), 0);
	}

	Sleep(250);
}

void NoClip::CheckVanillaMovement()
{
	byte movementTestByte;
	ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->movementInstructions),
		&movementTestByte, sizeof(movementTestByte), 0);
	if (movementTestByte == '0x90')
	{
		vanillaMovementIsActive = false;
	}
	else
	{
		vanillaMovementIsActive = true;
	}
}

void NoClip::MovePlayer(std::string direction)
{
			if (noClipIsActive)
			{
				// Get player's current position and rotation
				ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerXPosition), &playerX, sizeof(playerX), 0);
				ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerYPosition), &playerY, sizeof(playerY), 0);
				ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerZPosition), &playerZ, sizeof(playerZ), 0);
				ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerXRotation), &playerPitch, sizeof(playerPitch), 0);
				ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerYRotation), &playerYaw, sizeof(playerYaw), 0);

				// Modify Yaw for sideways directions
				if (direction == "left")
				{
					playerYaw += 90;
				}
				if (direction == "right")
				{
					playerYaw -= 90;
				}

				// Convert rotational degrees to radians
				playerPitch = playerPitch * (pi / 180);
				playerYaw = playerYaw * (pi / 180);

				// Calculate forward vector using rotations
				vectorX = -(cos(playerPitch) * sin(playerYaw));
				vectorY = sin(playerPitch);
				vectorZ = cos(playerPitch) * cos(playerYaw);

				// Apply movement speed to vector
				vectorX = vectorX * movementSpeed;
				vectorY = vectorY * movementSpeed;
				vectorZ = vectorZ * movementSpeed;

				// Add vector to coordinates modified by direction
				if (direction == "forward")
				{
					playerX += vectorX;
					playerY += vectorY;
					playerZ += vectorZ;
				}
				if (direction == "left")
				{
					playerX += vectorX;
					playerZ += vectorZ;
				}
				if (direction == "backward")
				{
					playerX -= vectorX;
					playerY -= vectorY;
					playerZ -= vectorZ;
				}
				if (direction == "right")
				{
					playerX += vectorX;
					playerZ += vectorZ;
				}
				
				// Apply new coordinates to player position
				WriteProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerXPosition), &playerX, sizeof(playerX), 0);
				WriteProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerYPosition), &playerY, sizeof(playerY), 0);
				WriteProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerZPosition), &playerZ, sizeof(playerZ), 0);
			}
}