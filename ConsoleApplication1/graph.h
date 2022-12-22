// abstract class graph
// abstract data type specification for graph data structure
// includes methods that are representation independent

#ifndef graph_
#define graph_

#include "edge.h"
#include "vertexIterator.h"
#include "myExceptions.h"
#include <queue>
using namespace std;

template<class T>
class graph 
{
   public:
      virtual ~graph() {}
      // ADT methods
      virtual int numberOfVertices() const = 0;
      virtual int numberOfEdges() const = 0;
      virtual bool existsEdge(int, int) const = 0;
      virtual void insertEdge(edge<T>*) = 0;
      virtual void eraseEdge(int, int) = 0;
      virtual int degree(int) const = 0;
      virtual int inDegree(int) const = 0;
      virtual int outDegree(int) const = 0;
      //other methods
      virtual bool directed() const = 0;
      virtual bool weighted() const = 0;
      virtual vertexIterator<T>* iterator(int) = 0;
      virtual void output(ostream&) const = 0;

	  bool cycle();
};

template<class T>
bool graph<T>::cycle()
{
	if (directed())
		throw undefinedMethod("cycle() for directed graph undefined");
	int n = numberOfVertices();
	int e = numberOfEdges();
	if (e >= n)return true;
	//bfs
	int* mark = new int[n + 1];
	for (int i = 1; i <= n; i++)
		mark[i] = 0;
	for (int i = 1; i <= n; i++)
	{
		if (mark[i] == 0)
		{
			queue<int> q;
			q.push(i);
			while (q.size())
			{
				int currentVertrix = q.front();
				q.pop();
				mark[currentVertrix] = 2;
				vertexIterator<T>* it = iterator(currentVertrix);
				int tmp;
				while (tmp = it->next())
				{
					switch (mark[tmp])
					{
					case(0):
						mark[tmp] = 1;
						q.push(tmp);
						break;
					case(1):
						delete[] it, mark;
						return true;
					case(2):
						break;
					}
				}
				delete[] it;
			}
		}
	}
	delete[] mark;
	return false;
}
#endif
