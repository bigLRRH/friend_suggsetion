#pragma once
#include "vertexIterator.h"
#include "graphArrayList.h"

class myIterator : public vertexIterator<bool>
{
public:
    myIterator(graphArrayList* theRow, int thePosition = -1)
    {
        row = theRow;
        position = thePosition;
    }

    ~myIterator() {}

    int next()
    { // Return next vertex if any. Return 0 if no next vertex.
        if (position >= row->size()-1)
            return 0;
        int nextVertex = row->get(++position);
        return nextVertex;
    }

    int next(bool& theWeight)
    { // Return next vertex if any. Return 0 if no next vertex.
      // Set theWeight = edge weight.
        if (position >= row->size()-1)
            return 0;
        int nextVertex = row->get(++position);
        theWeight = true;
        return nextVertex;
    }

protected:
    graphArrayList* row; // row of adjacency arrayList
    int position;
};