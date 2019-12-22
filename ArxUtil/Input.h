#pragma once
#include "Keys.h"
#include "NoClip.h"
#include "Vacuum.h"
#include "Teleport.h"
#include "Freeze.h"
#include "Telekinesis.h"

class Input
{
	
public:

	Keys * keys;
	NoClip * noClip;
	Teleport * teleport;
	Vacuum * vacuum;
	Freeze * freeze;
	Telekinesis * telekinesis;

	void Listener();
};