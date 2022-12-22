#include "arrayGraph.h"
#include "unweightedEdge.h"
#include <random>
#include <functional>
#include "friendNet.h"
#include "friend_suggestion_list.h"
using namespace std;

void randGraph(arrayGraph&);
//测试程序
int main()
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, 20);
	friend_suggestion_list** r1, **r2;
	int flag = 0;
	for (int i = 0; i < 2; i++)
	{
		int numberOfVertrices = distribution(generator);
		friendNet g(numberOfVertrices);
		randGraph(g);
		r1 = g.recommend_version_1();
		r2 = g.recommend_version_2();
		for (int i = 1; i <= g.numberOfVertices(); i++)
		{
			for (int j = 0; j < r1[i]->size(); i++)
			{
				if (r1[i]->get(j) != r2[i]->get(j))
				{
					flag = 1;
					break;
				}
			}
		}
	}
	cout << flag << endl;
	return 0;
}

void randGraph(arrayGraph& _G)
{//随机生成图（不一定是连通图）
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0,_G.numberOfVertices()* (_G.numberOfVertices()-1));
	int insertEdges = distribution(generator);//随机生成插入边数
	distribution = uniform_int_distribution<int>(1, _G.numberOfVertices());
	auto dice = bind(distribution, generator);
	while (insertEdges--)
	{
		//随机生成边
		int v1 = dice(),
			v2 = dice();
		while(v1==v2)
			v2 = dice();
		unweightedEdge* e = new unweightedEdge(v1, v2);
		_G.insertEdge(e);
		delete e;
	}
}