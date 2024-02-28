#include "Countries.h"

Countries::Countries()
{
	countries.reserve(2048);
}

Countries::Countries(int i)
{
	countries.reserve((2048+i));
}

Countries::~Countries()
{
	countries.~vector();
}

std::string* Countries::findCountry(std::string s)
{
	auto it = std::find(countries.begin(), countries.end(), s);
	if (it == countries.end())
		return NULL;
	return &(*it);
	//auto* it2 = it._Ptr;
	//return &(*it2);
}

void Countries::pushCountry(std::string str)
{
	countries.emplace_back(str);
}
