#include <iostream>
#include <Windows.h>
#include "Menu.h"

void Menu::Setup()
{
	// Set up display properties of console window
	handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	console = GetConsoleWindow();
	GetWindowRect(console, &rectangle);
	MoveWindow(console, rectangle.left, rectangle.top, newWidth, newHeight, TRUE);

	Update();
}

void Menu::Update()
{
	system("cls");
	system("title Arx Libertatis Utility 1.0");

	// Title
	SetConsoleTextAttribute(handleConsole, white);
	std::cout << "Arx Fatalis Utility 1.0 by Slicin\n\n";

	// Option
	if (noClip->noClipIsActive)
	{
		SetConsoleTextAttribute(handleConsole, green);
	}

	std::cout << "[" << keys->noClipToggle << "] Toggle No Clip Mode\n";
	SetConsoleTextAttribute(handleConsole, white);

	// Option
	std::cout << "[ENTER] Teleport to Nearest Entity\n";

	// Option
	std::cout << "[" << keys->vacuumItems << "] Vacuum Items\n";

	// Option
	std::cout << "[" << keys->vacuumCreatures << "] Vacuum Creatures\n";

	// Option
	std::cout << "[" << keys->vacuumContainers << "] Vacuum Containers\n";

	// Option
	std::cout << "[CAPS] Freeze/Unfreeze Creature\n";

	// Option
	std::cout << "[ALT] Telekinetic Move\n";

	// Option
	std::cout << "[JK] Telekinetic Rotate\n";
}