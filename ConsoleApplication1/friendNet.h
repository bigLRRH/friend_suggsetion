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
	//对一个人推荐好友
	friend_suggestion_list* recommend_for_one(int theVertrix)
	{
		friend_suggestion_list* fsl = new friend_suggestion_list();
		potential_friend_tree pft;
		myIterator* it1 = iterator(theVertrix);
		int v1;//theVertrix的好友
		while (v1 = it1->next())
		{//遍历theVertrix的相邻顶点
			myIterator* it2 = iterator(v1);
			int v2;//theVertrix的相邻顶点
			while (v2 = it2->next())
			{//遍历v2的相邻顶点
				pft.push(v2);
			}
			delete it2;
		}
		delete it1;
		it1 = iterator(theVertrix);
		while (v1 = it1->next())//删除theVertrix的好友
			pft.erase(v1);
		delete it1;
		pft.convert_to_fsl(fsl);//pft转换为fsl
		fsl->sort();//好友权重降序
		return fsl;
	}

	friend_suggestion_list** recommend_version_1()
	{//好友推荐算法(暴力求解)
  //返回潜在好友集合以权重为降序
		friend_suggestion_list** rt = new friend_suggestion_list * [n + 1];
		for (int v = 1; v <= n; v++)
		{//遍历每个顶点
			rt[v] = recommend_for_one(v);
		}
		return rt;
	}

	friend_suggestion_list** recommend_version_2()
	{
		friend_suggestion_list** rt = new friend_suggestion_list * [n + 1];
		potential_friend_tree* pft = new potential_friend_tree[n + 1];
		for (int v = 1; v <= n; v++)
		{//遍历每个顶点
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
			int v1;//v的相邻顶点
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