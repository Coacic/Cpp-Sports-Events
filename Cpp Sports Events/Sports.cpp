#include "Sports.h"

std::ostream& operator<<(std::ostream& os, const Sports& s)
{
	return os;
}

Sports::~Sports()
{
	sports.~vector();
}

Sports::Sports()
{
	sports.reserve(1024);
}

Sports::Sports(int i)
{
	sports.reserve(i);
}

std::string* Sports::getSport(int i)
{
	auto itEnd = sports.begin();
	if (i >= sports.size())
		return &(*sports.end());
	std::advance(itEnd, i);
	return &(*itEnd);
}

std::string* Sports::findSport(std::string _sport)
{
	auto it = std::find(sports.begin(), sports.end(), _sport);
	if (it == sports.end())
		return NULL;
	return &*it;
}

void Sports::pushSport(std::string _sport)
{
	sports.emplace_back(_sport);
}
