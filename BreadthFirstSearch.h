#pragma once
#include "PathFinding.h"
class BreadthFirstSearch :
	public IPathFinding
{
public:
	bool FindPath(Pos start, Pos target, Map* map);
	void DrawPath();
	unsigned int GetTimeSpent();
private:
	deque<Cell*> OpenList;
	deque<Cell*> m_result;
};