#pragma once

class Keys
{

public:

	// NoClip
	char noClipToggle = 'Z';
	char noClipMoveForward = 'W';
	char noClipMoveLeft = 'A';
	char noClipMoveBackward = 'S';
	char noClipMoveRight = 'D';

	// Teleport
	int teleportNear = VK_RETURN;

	// Vacuum
	char vacuumItems = '4';
	char vacuumCreatures = '5';
	char vacuumContainers = '6';

	// Freeze
	int freezeCreature = VK_CAPITAL;

	// Drag
	int dragEntity = VK_MENU; // ALT
	char rotateEntityLeft = 'J';
	char rotateEntityRight = 'K';
};