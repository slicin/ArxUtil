#pragma once
#include <Windows.h>
#include "NoClip.h"
#include "Keys.h"

class Vacuum;

class Menu
{

public:

	NoClip * noClip;
	Vacuum * vacuum;
	Keys * keys;

	HANDLE handleConsole;
	HWND console;
	RECT rectangle;

	int newWidth = 500;
	int newHeight = 400;
	int white = 15;
	int green = 10;

	void Setup();
	void Update();
};
