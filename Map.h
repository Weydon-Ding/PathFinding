#pragma once
#include "Base.h"
struct Cell
{
	int x, y;//�߼�λ��
	int mask;
	Cell* from;
	static Size size;
	Cell()
	{
		x = y = 0;
		mask = 1;
		from = NULL;
	}
	//double left, bottom, top, right;//����λ��
	//bool operator==(const Cell& another) const { return (this->x == another.x && this->y == another.y); }
	//float GetDistance(const Cell& another) const { return 0.0f; };
	bool Walkable()
	{
		return (abs(mask) == 1);
	}
	bool Checked()
	{
		return (mask < 0);
	}
	void Draw(float red, float green, float blue) const
	{
		glColor3f(red, green, blue);
		float left, bottom, right, top;
		left = x;
		bottom = y;
		right = x + Cell::size.w;
		top = y + Cell::size.h;
		glRectf(left, bottom, right, top);
	}
};

class Map
{
public:
	Map();
	~Map();
	void Load();
	void Draw();
	void Reset();
	void SetCol(int nCol) { m_nCol = nCol; }
	void SetRow(int nRow) { m_nRow = nRow; }
	int GetCol() { return m_nCol; }
	int GetRow() { return m_nRow; }
	double GetWidth() { return m_dWidth; }
	double GetHeight() { return m_dHeight; }
	Cell& GetCell(int x, int y);
	void SetCellMask(int x, int y, int mask);
	void GetCellNeighbors(const Cell& cell, Cell** ppNeighbors, int& num);
	void Bg2World(int bgX, int bgY, double& posX, double& posY) const;
	void World2Bg(double posX, double posY, int& bgX, int& bgY) const;
	void Cell2World(int x, int y, double& posX, double& posY) const;
	void World2Cell(double posX, double posY, int& x, int& y) const;
	void DrawGrid(float red, float green, float blue);

private:
	Cell m_Cells[MAX_CELL_NUM];	// ����ȫ��Cell��Ϣ��Ӧ�Ե�ͼ��ʵʱ�仯
	int m_nCol, m_nRow;			// ��ͼ���߼���С
	double m_dWidth, m_dHeight;	// ��ͼ�������С
	double m_dX, m_dY;			// ��ͼ������λ��
};
