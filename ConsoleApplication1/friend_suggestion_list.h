#ifndef _friend_suggestion_list
#define _friend_suggestion_list

#include "arrayList.h"
#include "potential_friend.h"
#include "potential_friend_tree.h"

class friend_suggestion_list :public arrayList<potential_friend>
{
public:
	void sort()
	{
			merge_sort(0, listSize - 1);
	}
	void merge_sort(int front, int end)
	{
		if (front >= end)return;
		int mid = (front + end) / 2;
		merge_sort(front, mid);
		merge_sort(mid, end);
		merge(front, mid, end);
	}
	void merge(int front, int mid, int end)
	{
		potential_friend* tmp = new potential_friend[end - front + 1];
		int i = 0, leftIdx = front, rightIdx = mid;
		while (leftIdx < mid && rightIdx <= end)
		{
			if (element[leftIdx].weight > element[rightIdx].weight)
				tmp[i] = element[leftIdx++];
			else
				tmp[i] = element[rightIdx++];
		}
		while (leftIdx < mid)
			tmp[i] = element[leftIdx++];
		while (rightIdx <= end)
			tmp[i] = element[rightIdx++];
		i = 0;
		while (i <= end)
		{
			element[i] = tmp[i];
			i++;
		}
	}
};

#endif // !_friend_suggestion_list

