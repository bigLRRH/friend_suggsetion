#ifndef _friendNet
#define _friendNet

#include "arrayGraph.h"
#include "potential_friend.h"
#include "potential_friend_tree.h"
#include "friend_suggestion_list.h"

class friendNet :public arrayGraph
{
public:
	friendNet(int numberOfVertrices = 0) :arrayGraph(numberOfVertrices) {}
	//��һ�����Ƽ�����
	friend_suggestion_list* recommend_for_one(int theVertrix)
	{
		friend_suggestion_list* fsl = new friend_suggestion_list();
		potential_friend_tree pft;
		myIterator* it1 = iterator(theVertrix);
		int v1;//theVertrix�ĺ���
		while (v1 = it1->next())
		{//����theVertrix�����ڶ���
			myIterator* it2 = iterator(v1);
			int v2;//theVertrix�����ڶ���
			while (v2 = it2->next())
			{//����v2�����ڶ���
				pft.push(v2);
			}
			delete it2;
		}
		delete it1;
		it1 = iterator(theVertrix);
		while (v1 = it1->next())//ɾ��theVertrix�ĺ���
			pft.erase(v1);
		delete it1;
		pft.convert_to_fsl(fsl);//pftת��Ϊfsl
		fsl->sort();//����Ȩ�ؽ���
		return fsl;
	}

	friend_suggestion_list** recommend_version_1()
	{//�����Ƽ��㷨(�������)
  //����Ǳ�ں��Ѽ�����Ȩ��Ϊ����
		friend_suggestion_list** rt = new friend_suggestion_list * [n + 1];
		for (int v = 1; v <= n; v++)
		{//����ÿ������
			rt[v] = recommend_for_one(v);
		}
		return rt;
	}

	friend_suggestion_list** recommend_version_2()
	{
		friend_suggestion_list** rt = new friend_suggestion_list * [n + 1];
		potential_friend_tree* pft = new potential_friend_tree[n + 1];
		for (int v = 1; v <= n; v++)
		{//����ÿ������
			for (int i = 1; i < aList[v].size(); i++)
			{
				for (int j = i; j < aList[v].size(); j++)
				{
					pft[i].push(j);
					pft[j].push(i);
				}
			}
		}
		for (int v = 1; v <= n; v++)
		{
			myIterator* it = iterator(v);
			int v1;//v�����ڶ���
			while (v1 = it->next())
				pft[v].erase(v1);
			delete it;
			rt[v] = new friend_suggestion_list;
			pft[v].convert_to_fsl(rt[v]);
			rt[v]->sort();
		}
		return rt;
	}
};

#endif // !_friendNet