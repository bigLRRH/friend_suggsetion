// array adjacency list representation of a graph

#ifndef arrayGraph_
#define arrayGraph_


#include <iostream>
#include <sstream>
#include "arrayDiGraph.h"
#include "unweightedEdge.h"
#include "arrayList.h"
#include <queue>
#include "myIterator.h"

using namespace std;

class arrayGraph : public arrayDiGraph
{
public:
	arrayGraph(int numberOfVertices = 0)
		: arrayDiGraph(numberOfVertices) {}

	bool directed() const { return false; }

	void insertEdge(edge<bool>* theEdge)
	{// Insert an edge.
		int oldE = e;
		arrayDiGraph::insertEdge(theEdge);
		if (e > oldE)
		{// new edge
			arrayDiGraph::insertEdgeNoCheck(new unweightedEdge
			(theEdge->vertex2(), theEdge->vertex1()));
			e--;  // compenstate for extra increment
		}
	}

	void insertEdgeNoCheck(edge<bool>* theEdge)
	{// Insert an edge. No validation checks performed.
		arrayDiGraph::insertEdgeNoCheck(theEdge);
		arrayDiGraph::insertEdgeNoCheck(new unweightedEdge
		(theEdge->vertex2(), theEdge->vertex1()));
		e--;
	}

	void eraseEdge(int i, int j)
	{
		int oldE = e;
		arrayDiGraph::eraseEdge(i, j);
		if (oldE > e) // edge exists
		{
			arrayDiGraph::eraseEdge(j, i);
			e++;
		}
	}

	int degree(int theVertex) const
	{
		checkVertex(theVertex);
		return aList[theVertex].size();
	}

	int outDegree(int theVertex) const { return degree(theVertex); }

	int inDegree(int theVertex) const { return degree(theVertex); }
};
#endif
