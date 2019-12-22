#include <Windows.h>
#include <iostream>
#include <chrono>
#include "Input.h"

void Input::Listener()
{
	// =============== No Clip ===============
	// Toggle NoClip Mode
	if (GetAsyncKeyState(keys->noClipToggle))
	{
		noClip->ToggleNoClipMode();
	}
	// Move Forward
	if (GetAsyncKeyState(keys->noClipMoveForward))
	{
		noClip->MovePlayer("forward");
	}
	// Move Left
	if (GetAsyncKeyState(keys->noClipMoveLeft))
	{
		noClip->MovePlayer("left");
	}
	// Move Backward
	if (GetAsyncKeyState(keys->noClipMoveBackward))
	{
		noClip->MovePlayer("backward");
	}
	// Move Right
	if (GetAsyncKeyState(keys->noClipMoveRight))
	{
		noClip->MovePlayer("right");
	}

	// =============== Teleport ===============
	if (GetAsyncKeyState(keys->teleportNear))
	{
		teleport->TeleportToNearestEntity();
	}

	// =============== Vacuum ===============
	// Item Vacuum
	if (GetAsyncKeyState(keys->vacuumItems))
	{
		vacuum->CreateVacuum("item");
	}
	// Creature Vacuum
	if (GetAsyncKeyState(keys->vacuumCreatures))
	{
		vacuum->CreateVacuum("creature");
	}
	// Container Vacuum
	if (GetAsyncKeyState(keys->vacuumContainers))
	{
		vacuum->CreateVacuum("container");
	}

	// =============== Freeze ===============
	// Freeze/Unfreeze Entity
	if (GetAsyncKeyState(keys->freezeCreature))
	{
		freeze->FreezeUnfreezeCreature();
	}

	// =============== Telekinesis ===============
	// Drag Entity
	if (GetAsyncKeyState(keys->dragEntity))
	{
		telekinesis->DragEntity();
	}
	// Rotate Entity Right
	if (GetAsyncKeyState(keys->rotateEntityRight))
	{
		telekinesis->RotateEntity();
	}
	// Rotate Entity Left
	if (GetAsyncKeyState(keys->rotateEntityLeft))
	{
		telekinesis->RotateEntity();
	}
}