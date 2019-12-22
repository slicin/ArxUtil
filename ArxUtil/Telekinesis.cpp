#include <Windows.h>
#include <cmath>
#include "Telekinesis.h"

void Telekinesis::DragEntity()
{
	DWORD target;
	ReadProcessMemory(memory->handle, (LPVOID)memory->target, &target, sizeof(target), 0);

	if (target == noTarget)
	{
		return;
	}

	while (GetAsyncKeyState(keys->dragEntity))
	{
		// Get current player position
		ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerXPosition), &playerX, sizeof(playerX), 0);
		ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerYPosition), &playerY, sizeof(playerY), 0);
		ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerZPosition), &playerZ, sizeof(playerZ), 0);

		// Copy player position to destination
		destinationX = playerX;
		destinationY = playerY;
		destinationZ = playerZ;

		// Get current player rotation
		ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerXRotation), &playerPitch, sizeof(playerPitch), 0);
		ReadProcessMemory(memory->handle, (LPVOID)(memory->moduleBaseAddress + memory->playerYRotation), &playerYaw, sizeof(playerYaw), 0);

		// Convert rotational degrees to radians
		playerPitch = playerPitch * (pi / 180);
		playerYaw = playerYaw * (pi / 180);

		// Calculate forward vector using rotations
		vectorX = -(cos(playerPitch) * sin(playerYaw));
		vectorY = sin(playerPitch);
		vectorZ = cos(playerPitch) * cos(playerYaw);

		// Apply distance offset to vector
		vectorX = vectorX * distanceOffset;
		vectorY = vectorY * distanceOffset;
		vectorZ = vectorZ * distanceOffset;

		// Add vector to coordinates
		destinationX += vectorX;
		destinationY += vectorY;
		destinationZ += vectorZ;

		// Modify height so entities don't spawn at head height
		//destinationY += heightAdjust;

		// Write coordinates to entity
		WriteProcessMemory(memory->handle, (LPVOID)(target + memory->entityXPosition), &destinationX, sizeof(destinationX), 0);
		WriteProcessMemory(memory->handle, (LPVOID)(target + memory->entityYPosition), &destinationY, sizeof(destinationY), 0);
		WriteProcessMemory(memory->handle, (LPVOID)(target + memory->entityZPosition), &destinationZ, sizeof(destinationZ), 0);
	}
}

void Telekinesis::RotateEntity()
{
	DWORD target;
	ReadProcessMemory(memory->handle, (LPVOID)memory->target, &target, sizeof(target), 0);

	if (target == noTarget)
	{
		return;
	}

	while (GetAsyncKeyState(keys->rotateEntityRight))
	{
		// Get current entity rotation
		ReadProcessMemory(memory->handle, (LPVOID)(target + memory->entityXRotation), &entityPitch, sizeof(entityPitch), 0);
		ReadProcessMemory(memory->handle, (LPVOID)(target + memory->entityYRotation), &entityYaw, sizeof(entityYaw), 0);
		ReadProcessMemory(memory->handle, (LPVOID)(target + memory->entityZRotation), &entityRoll, sizeof(entityRoll), 0);

		// Add rotation
		entityYaw += rotationSpeed;

		// Apply rotation
		WriteProcessMemory(memory->handle, (LPVOID)(target + memory->entityYRotation), &entityYaw, sizeof(entityYaw), 0);
	}

	while (GetAsyncKeyState(keys->rotateEntityLeft))
	{
		// Get current entity rotation
		ReadProcessMemory(memory->handle, (LPVOID)(target + memory->entityXRotation), &entityPitch, sizeof(entityPitch), 0);
		ReadProcessMemory(memory->handle, (LPVOID)(target + memory->entityYRotation), &entityYaw, sizeof(entityYaw), 0);
		ReadProcessMemory(memory->handle, (LPVOID)(target + memory->entityZRotation), &entityRoll, sizeof(entityRoll), 0);

		// Add rotation
		entityYaw -= rotationSpeed;

		// Apply rotation
		WriteProcessMemory(memory->handle, (LPVOID)(target + memory->entityYRotation), &entityYaw, sizeof(entityYaw), 0);
	}
}