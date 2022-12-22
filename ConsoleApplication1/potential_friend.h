#ifndef _potential_friend
#define _potential_friend

#include <iostream>

class potential_friend
{
public:
	potential_friend(int _id = -1, int _weight = 1)
	{
		id = _id;
		weight = _weight;
	}
	~potential_friend() = default;

	bool operator==(const potential_friend& the_potential_friend)
	{
		if (id == the_potential_friend.id&&weight==the_potential_friend.weight)
			return true;
		else
			return false;
	}
	bool operator!=(const potential_friend& the_potential_friend)
	{
		if (id == the_potential_friend.id && weight == the_potential_friend.weight)
			return false;
		else
			return true;
	}
	friend ostream& operator<<(ostream& output, const potential_friend& the_potential_friend)
	{
		output << "id: " << the_potential_friend.id << " weight:" << the_potential_friend.weight;
		return output;
	}
public:
	int id;//好友
	int weight;//关系权重
};

#endif // !_potential_friend
