// array adjacency list representation of a digraph
#ifndef arrayDiGraph_
#define arrayDiGraph_

#include <iostream>
#include <sstream>
#include "graph.h"
#include "graphArrayList.h"
#include "unweightedEdge.h"
#include "vertexIterator.h"
#include "myExceptions.h"
#include "myIterator.h"

using namespace std;

class arrayDiGraph : public graph<bool>
{
protected:
    int n;                 // number of vertices
    int e;                 // number of edges
    graphArrayList *aList; // adjacency lists
public:
    arrayDiGraph(int numberOfVertices = 0)
    { // Constructor.
        if (numberOfVertices < 0)
            throw illegalParameterValue("number of vertices must be >= 0");
        n = numberOfVertices;
        e = 0;
        aList = new graphArrayList[n + 1];
    }
    ~arrayDiGraph() { delete[] aList; }

    int numberOfVertices() const { return n; }

    int numberOfEdges() const { return e; }

    bool directed() const { return true; }

    bool weighted() const { return false; }

    bool existsEdge(int i, int j) const
    { // Return true iff (i,j) is an edge.
        if (i < 1 || j < 1 || i > n || j > n || aList[i].indexOf(j) == -1)
            return false;
        else
            return true;
    }
    void insertEdge(edge<bool> *theEdge)
    { // Insert an edge.
        int v1 = theEdge->vertex1();
        int v2 = theEdge->vertex2();
        if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
        {
            ostringstream s;
            s << "(" << v1 << "," << v2
              << ") is not a permissible edge";
            throw illegalParameterValue(s.str());
        }

        if (aList[v1].indexOf(v2) == -1)
        { // new edge
            aList[v1].insert(0, v2);
            e++;
        }
    }

    void insertEdgeNoCheck(edge<bool> *theEdge)
    { // Insert an edge. No validation checks performed.
        aList[theEdge->vertex1()].insert(0, theEdge->vertex2());
        e++;
    }

    void eraseEdge(int i, int j)
    {
        if (i >= 1 && j >= 1 && i <= n && j <= n)
        {
            int v = aList[i].eraseElement(j);
            if (v != -1) // edge (i,j) did exist
                e--;
        }
    }

    void checkVertex(int theVertex) const
    { // Verify that i is a valid vertex.
        if (theVertex < 1 || theVertex > n)
        {
            ostringstream s;
            s << "no vertex " << theVertex;
            throw illegalParameterValue(s.str());
        }
    }

    int degree(int theVertex) const
    {
        throw undefinedMethod("degree() undefined");
    }

    int outDegree(int theVertex) const
    { // Return out-degree of vertex theVertex.
        checkVertex(theVertex);
        return aList[theVertex].size();
    }

    int inDegree(int theVertex) const
    {
        checkVertex(theVertex);

        // count in-edges at vertex theVertex
        int sum = 0;
        for (int j = 1; j <= n; j++)
            if (aList[j].indexOf(theVertex) != -1)
                sum++;

        return sum;
    }

   

    myIterator *iterator(int theVertex)
    { // Return iterator for vertex theVertex.
        checkVertex(theVertex);
        return new myIterator(&aList[theVertex]);
    }

    void output(ostream &out) const
    { // Output the adjacency arrayList.
        for (int i = 1; i <= n; i++)
            out << aList[i] << endl;
    }
};

// overload <<
ostream &operator<<(ostream &out, const arrayDiGraph &x)
{
    x.output(out);
    return out;
}
#endif
