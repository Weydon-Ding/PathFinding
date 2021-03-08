#pragma once
#include "PathFinding.h"
class DepthFirstSearch :
    public IPathFinding
{
public:
	virtual bool FindPath(Pos start, Pos target, Map* map);
	virtual void DrawPath();
	//virtual unsigned int GetTimeSpent() = 0;
private:
	stack<Cell*> OpenList;
	deque<Cell*> m_result;
};

