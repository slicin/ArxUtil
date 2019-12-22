#pragma once
#include "Keys.h"
#include "Memory.h"

class Telekinesis
{

public:

	Memory * memory;
	Keys * keys;

	DWORD noTarget = 0x0;

	float playerX, playerY, playerZ = 0;
	float playerPitch, playerYaw = 0;
	float destinationX, destinationY, destinationZ = 0;
	float entityPitch, entityYaw = 0, entityRoll;
	float vectorX, vectorY, vectorZ = 0;
	//float heightAdjust = 50;
	float pi = 3.14f;
	float distanceOffset = 200;
	float rotationSpeed = 0.05f;

	void DragEntity();
	void RotateEntity();
};