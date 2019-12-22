#pragma once
#include <vector>
#include "Memory.h"

class Freeze
{

public:

	Memory * memory;

	int frozen = 26;
	int unfrozen = 4104;
	std::vector<int> creatureIDs = { 8, 24, 4104, 4616 };

	void FreezeUnfreezeCreature();
};