#include "DepthFirstSearch.h"

bool DepthFirstSearch::FindPath(Pos start, Pos target, Map* map)
{
	if (m_result.size() > 0)
	{
		m_result.clear();
	}
	Cell* pStart = &map->GetCell(start.x, start.y);
	Cell* pTarget = &map->GetCell(target.x, target.y);
	//��pStart����OpenList
	pStart->mask = -pStart->mask;
	OpenList.push(pStart);
	//ѭ��
	while (!OpenList.empty())
	{
		//ȡ�б�ͷ������Լ��ǲ���Target
		Cell* pCur = OpenList.top();
		OpenList.pop();
		pCur->Draw(GL_AOI);
		//����
		if (pCur == pTarget)
		{
			for (int i = 1; i < OpenList.size(); ++i)
			{
				OpenList.top()->Draw(GL_AOI);
				OpenList.pop();
			}
			//����ѭ������Դ
			while (pCur != NULL)
			{
				m_result.push_back(pCur);
				pCur = pCur->from;
			}
			return true;
		}
		//�����ǣ���δ�����ھӼ��뵽OpenList
		Cell* ppNeighbors[8];
		int count;
		map->GetCellNeighbors(*pCur, ppNeighbors, count);
		for (int i = 0; i < count; ++i)
		{
			Cell* pNeighbor = ppNeighbors[i];
			if (pNeighbor->Walkable() && !pNeighbor->Checked())
			{
				pNeighbor->from = pCur;
				pNeighbor->mask = -pNeighbor->mask;
				OpenList.push(pNeighbor);
			}
		}
	}
	return false;
}

void DepthFirstSearch::DrawPath()
{
	for (int i = 0; i < m_result.size(); ++i)
	{
		m_result[i]->Draw(GL_PURPLE);
	}
}

