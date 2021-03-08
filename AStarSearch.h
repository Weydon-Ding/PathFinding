#pragma once
#include "PathFinding.h"
class AStarSearch :
    public IPathFinding
{
public:
	virtual bool FindPath(Pos start, Pos target, Map* map);
	virtual void DrawPath();

private:
};

