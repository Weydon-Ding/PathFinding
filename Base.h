#pragma once
#ifndef __PATH_FINDING_H__
#define __PATH_FINDING_H__
#include <windows.h>
#include "glut.h"
#include <stack>
#include <deque>
#include <queue>
using std::stack;
using std::deque;
using std::priority_queue;
#define	GL_WHITE	1.0f,1.0f,1.0f
#define	GL_BLACK	0.0f,0.0f,0.0f
#define	GL_GRAY		0.5f,0.5f,0.5f
#define GL_RED		1.0f,0.0f,0.0f
#define GL_GREEN	0.0f,1.0f,0.0f
#define GL_BLUE		0.0f,0.0f,1.0f
#define GL_PURPLE	1.0f,0.0f,1.0f
#define GL_AOI		0.0f,1.0f,1.0f
#define GL_YELLOW	1.0f,1.0f,0.0f

#define MAP_POS_X	0.0
#define MAP_POS_Y	0.0
#define MAP_WIDTH	50.0
#define MAP_HEIGHT	50.0

#define MAP_ROW_NUM 50
#define MAP_COL_NUM 50
const int MAX_CELL_NUM = MAP_ROW_NUM * MAP_COL_NUM;
struct Pos
{
	double x, y;
};
struct Size
{
	double w, h;
};

static inline void DrawLine(Pos A, Pos B)
{
	glBegin(GL_LINES);
	glVertex2d(A.x, A.y);
	glVertex2d(B.x, B.y);
	glEnd();
}

// wnd
#define WND_POS_X	2100
#define WND_POS_Y	100
#define WND_WIDTH	1280
#define WND_HEIGHT	1024
#define WND_NAME	"PathFinding"

int Manhattan(int x1, int y1, int x2, int y2, double D)
{
	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);
	return D * (dx + dy);
}
int Diagonal(int x1, int y1, int x2, int y2, double D1, double D2)
{
	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);
	return D1 * (dx + dy) + (D2 - 2 * D1) * min(dx, dy);
}
#define Chebyshev(x1, y1, x2, y2, D) Diagonal(x1, y1, x2, y2, D, D)
#define Octile(x1, y1, x2, y2, D) Diagonal(x1, y1, x2, y2, 1, D * sqrt(2))
int Euclidean(int x1, int y1, int x2, int y2, double D)
{
	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);
	return D * sqrt(dx * dx + dy * dy);
}
#endif // !__PATH_FINDING_H__