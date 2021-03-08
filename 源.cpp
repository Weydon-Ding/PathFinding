#include "BreadthFirstSearch.h"
#include "DepthFirstSearch.h"
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

Pos g_StartPos = { 2.0,1.0 };
Pos g_TargetPos = { 2.0,4.0 };
Map g_Map;

bool refresh = false;
bool g_bLock = false;
int g_nMask = 0;
IPathFinding* pPathFinding = NULL;

void Render()
{
	g_Map.Draw();
	g_Map.Reset();
	if (pPathFinding && pPathFinding->FindPath(g_StartPos, g_TargetPos, &g_Map))
	{
		pPathFinding->DrawPath();
	}

	Cell& cell1 = g_Map.GetCell(g_StartPos.x, g_StartPos.y);
	cell1.Draw(GL_GREEN);

	Cell& cell2 = g_Map.GetCell(g_TargetPos.x, g_TargetPos.y);
	cell2.Draw(GL_RED);

	g_Map.DrawGrid(GL_WHITE);
	//glViewport(1024, 0, 256, 1024);
	//// UI
	//const char* string = "FPS";
	//int len, i;
	//glColor3f(GL_RED);
	//glRasterPos2f(0, 49);
	//len = (int)strlen(string);
	//for (i = 0; i < len; i++)
	//{
	//	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	//}
	glEnd();
}

void display(void)
{
	glClearColor(GL_BLACK, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(MAP_POS_X, MAP_POS_X + MAP_WIDTH, MAP_POS_Y, MAP_POS_Y + MAP_HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, min(WND_WIDTH, WND_HEIGHT), min(WND_WIDTH, WND_HEIGHT));

	Render();

	glutSwapBuffers();
}
void reshape(int w, int h)
{
	//glViewport(0, 0, min(w, h), min(w, h));
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 32:
		if (pPathFinding)
		{
			delete pPathFinding;
		}
		pPathFinding = new DepthFirstSearch();
		break;
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
		g_nMask = key - 48;
		break;
	}
	printf("key:%c\n", key);
	glutPostRedisplay();  //产生重绘回调
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			printf("鼠标左键按下:%d,%d\n", x, y);
			double worldX, worldY;
			g_Map.Bg2World(x, y, worldX, worldY);
			
			int cellX, cellY;
			g_Map.World2Cell(worldX, worldY, cellX, cellY);

			Cell& cell = g_Map.GetCell(cellX, cellY);
			if (cell.Walkable())
			{
				g_StartPos = { worldX, worldY };
			}
			printf("Cell坐标:%d,%d\n", cellX, cellY);
		}
		else if (state == GLUT_UP)
		{
			printf("鼠标左键抬起:%d,%d\n", x, y);
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)
		{
			printf("鼠标中键按下:%d,%d\n", x, y);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			printf("鼠标右键按下:%d,%d\n", x, y);
			double worldX, worldY;
			g_Map.Bg2World(x, y, worldX, worldY);

			int cellX, cellY;
			g_Map.World2Cell(worldX, worldY, cellX, cellY);

			Cell& cell = g_Map.GetCell(cellX, cellY);
			if (cell.Walkable())
			{
				g_TargetPos = { worldX, worldY };
			}
			printf("Cell坐标:%d,%d\n", cellX, cellY);
		}
		else if (state == GLUT_UP)
		{
			printf("鼠标右键抬起:%d,%d\n", x, y);
		}
		break;
	}
	glutPostRedisplay();
}
void motion(int x, int y)
{
	//if (g_bLock)
	//{
	//	int cellX, cellY;
	//	g_Map.World2Cell(x * 25 / 1024, (1024 - y) * 25 / 1024, cellX, cellY);
	//	g_Map.SetCellMask(cellX, cellY, g_nMask);
	//	printf("Cell坐标:%d,%d\n", cellX, cellY);
	//	glutPostRedisplay();
	//}
}
void idle(void)
{
	if (refresh)
	{
		glutPostRedisplay(); //空闲时强制重绘，这样不断的调用display
	}
}
void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, timer, 0);
}

int main(int argc, char** argv)
{
	g_Map.Load();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(WND_POS_X, WND_POS_Y);
	glutInitWindowSize(WND_WIDTH, WND_HEIGHT);
	glutCreateWindow(WND_NAME);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	//glutIdleFunc(idle);
	//glutTimerFunc(100, timer, 0);

	glutMainLoop();
	return 0;
}