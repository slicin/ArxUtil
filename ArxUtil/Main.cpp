// Tested on Arx Libertatis 1.1.2 x86

#include <Windows.h>
#include <iostream>
#include "Memory.h"
#include "NoClip.h"
#include "Teleport.h"
#include "Vacuum.h"
#include "Freeze.h"
#include "Telekinesis.h"
#include "ProcessUtility.h"
#include "Input.h"
#include "Keys.h"
#include "Menu.h"

int main()
{
	bool running = true;
	bool showProcessDebugInfo = false;

	double startTime = GetTickCount();
	double currentTime;

	ProcessUtility processUtility;
	Memory memory;
	NoClip noClip;
	Teleport teleport;
	Vacuum vacuum;
	Freeze freeze;
	Telekinesis telekinesis;
	Keys keys;
	Input input;
	Menu menu;

	Memory * memoryPtr = &memory;
	NoClip * noClipPtr = &noClip;
	Teleport * teleportPtr = &teleport;
	Vacuum * vacuumPtr = &vacuum;
	Freeze * freezePtr = &freeze;
	Telekinesis * telekinesisPtr = &telekinesis;
	Keys * keysPtr = &keys;
	Menu * menuPtr = &menu;

	processUtility.memory = memoryPtr;
	processUtility.noClip = noClipPtr;
	noClip.memory = memoryPtr;
	noClip.menu = menuPtr;
	teleport.memory = memoryPtr;
	vacuum.memory = memoryPtr;
	vacuum.menu = menuPtr;
	freeze.memory = memoryPtr;
	telekinesis.memory = memoryPtr;
	telekinesis.keys = keysPtr;
	input.noClip = noClipPtr;
	input.teleport = teleportPtr;
	input.vacuum = vacuumPtr;
	input.keys = keysPtr;
	input.freeze = freezePtr;
	input.telekinesis = telekinesisPtr;
	menu.noClip = noClipPtr;
	menu.vacuum = vacuumPtr;
	menu.keys = keysPtr;

	processUtility.processName = "Arx Libertatis 1.1.2";
	processUtility.Initialize();
	if (processUtility.handleWindow == 0)
	{
		std::cout << "Window not found. Are you sure Arx Libertatis is running?\n\n";
		system("pause");
		return 0;
	}

	if (showProcessDebugInfo)
	{
		std::cout << "[PROCESS DEBUG INFO]"
			<< "\nProcess Name: " << processUtility.processName
			<< "\nWindow Handle: " << processUtility.handleWindow
			<< "\nProcess ID: " << processUtility.processID
			<< "\nProcess Handle: " << memory.handle
			<< "\nModule Base Address: " << std::hex << memory.moduleBaseAddress;
	}

	// Begin menu
	menu.Setup();

	// =============== Main Loop ===============
	while (running)
	{
		// Set clock for running main loop
		currentTime = GetTickCount() - startTime;

		if (currentTime >= 10) // 100 iterations per second
		{
			// Only process input if Arx is the foreground window
			if (GetForegroundWindow() == processUtility.handleWindow)
			{
				input.Listener();
			}

			//Reset the timer
			startTime = GetTickCount();
		}
	}

	std::cout << "\n\n";
	system("pause");

	return 0;
}