
// Extension of arrayList to include a method to erase by matching element field
// This class is for use by the adjacent array graph classes
#ifndef graphArrayList_
#define graphArrayList_

#include "arrayList.h"

using namespace std;

class graphArrayList : public arrayList<int>
{
public:
  int eraseElement(int theVertex)
  { // Delete node with element == theVertex. Return the index to
    // deleted element. Return -1 if no matching element.
    int theIndex = indexOf(theVertex);
    if (theIndex != -1)
       erase(theIndex);
    return theIndex;
  }
};
#endif