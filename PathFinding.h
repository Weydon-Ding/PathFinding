#pragma once
#include "Map.h"
class IPathFinding
{
public:
	virtual bool FindPath(Pos start, Pos target, Map* map) = 0;
	virtual void DrawPath() = 0;
	//virtual unsigned int GetTimeSpent() = 0;
};
