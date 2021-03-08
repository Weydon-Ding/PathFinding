#include "Map.h"
Size Cell::size = { 1,1 };
Map::Map()
{
	m_nRow = 0;
	m_nCol = 0;
	m_dWidth = 0.0;
	m_dHeight = 0.0;
	m_dX = m_dY = 0.0;
}

Map::~Map()
{
}

void Map::Load()
{
	m_nRow = MAP_ROW_NUM;
	m_nCol = MAP_COL_NUM;
	m_dWidth = MAP_WIDTH;
	m_dHeight = MAP_HEIGHT;
	m_dX = MAP_POS_X;
	m_dY = MAP_POS_Y;
	for (int i = 0; i < m_nCol; ++i)
	{
		for (int j = 0; j < m_nRow; ++j)
		{
			Cell& cell = GetCell(i, j);
			cell.x = i;
			cell.y = j;
		}
	}
	Cell::size.w = m_dWidth / m_nCol;
	Cell::size.h = m_dHeight / m_nRow;
}

void Map::Draw()
{
	for (int i = 0; i < m_nCol; ++i)
	{
		for (int j = 0; j < m_nRow; ++j)
		{
			Cell& cell = GetCell(i, j);
			switch (abs(cell.mask))
			{
			case 0:
				cell.Draw(GL_BLACK);
				break;
			case 1:
				cell.Draw(GL_GRAY);
				break;
			case 2:
				cell.Draw(GL_BLUE);
				break;
			}
		}
	}
}
void Map::Reset()
{
	for (int i = 0; i < MAX_CELL_NUM; ++i)
	{
		m_Cells[i].mask = abs(m_Cells[i].mask);
		m_Cells[i].from = NULL;
	}
}
Cell& Map::GetCell(int x, int y)
{
	if (x >= m_nRow)x = m_nRow - 1;
	return m_Cells[x * m_nCol + y];
}

void Map::SetCellMask(int x, int y, int mask)
{
	m_Cells[x * m_nCol + y].mask = mask;
}

void Map::GetCellNeighbors(const Cell& cell, Cell** ppNeighbors, int& num)
{
	num = 0;
	int iMin = cell.x > 0 ? -1 : 0;
	int jMin = cell.y > 0 ? -1 : 0;
	int iMax = cell.x < m_nRow - 1 ? 2 : 1;
	int jMax = cell.y < m_nCol - 1 ? 2 : 1;
	//(i,j) 
	//|5(-1,+1)|6( 0,+1)|7(+1,+1)|
	//|3(-1, 0)|  Cell  |4(+1, 0)|
	//|0(-1,-1)|1( 0,-1)|2(+1,-1)|
	for (int j = jMin; j < jMax; ++j)
	{
		for (int i = iMin; i < iMax; ++i)
		{
			if (0 != i || 0 != j)
			{
				if (abs(i) + abs(j) == 2) continue;
				Cell& pNeighbor = GetCell(cell.x + i, cell.y + j);
				if (2 == pNeighbor.mask)continue;
				ppNeighbors[num] = &pNeighbor;
				++num;
			}
		}
	}
	//for (int j = jMin; j < jMax; ++j)
	//{
	//	for (int i = iMin; i < iMax; ++i)
	//	{
	//		if (0 != i || 0 != j)
	//		{
	//			if (abs(i) + abs(j) == 1) continue;
	//			Cell& pNeighbor = GetCell(cell.x + i, cell.y + j);
	//			if (2 == pNeighbor.mask)continue;
	//			ppNeighbors[num] = &pNeighbor;
	//			++num;
	//		}
	//	}
	//}
}

void Map::Bg2World(int bgX, int bgY, double& posX, double& posY) const
{
	posX = bgX * MAP_WIDTH / min(WND_WIDTH, WND_HEIGHT);
	posY = (min(WND_WIDTH, WND_HEIGHT) - bgY) * MAP_HEIGHT / min(WND_WIDTH, WND_HEIGHT);
}

void Map::World2Bg(double posX, double posY, int& bgX, int& bgY) const
{
}

void Map::Cell2World(int x, int y, double& posX, double& posY) const
{
	posX = (x + 0.5) * Cell::size.w;
	posY = (y + 0.5) * Cell::size.h;
}

void Map::World2Cell(double posX, double posY, int& x, int& y) const
{
	x = (int)(posX / Cell::size.w);
	y = (int)(posY / Cell::size.h);
}

void Map::DrawGrid(float red, float green, float blue)
{
	glColor3f(red, green, blue);
	for (int i = 0; i <= m_nRow; i++)
	{
		DrawLine({ m_dX, m_dY + i * Cell::size.h }, { m_dX + m_nCol * Cell::size.w, m_dY + i * Cell::size.h });
	}	
	for (int j = 0; j <= m_nCol; j++)
	{
		DrawLine({ m_dX + j * Cell::size.w, m_dY }, { m_dX + j * Cell::size.w, m_dY + m_nRow * Cell::size.h });
	}
}