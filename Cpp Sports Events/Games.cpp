#include "Games.h"

Games::Games(int i)
{
	games.reserve(i);
}

Games::Games()
{
	games.reserve(1024);
}

Games::~Games()
{
	games.~vector();
}

int Games::push(std::string _games)
{
	games.emplace_back(_games);
	return getSize()-1;
}

int Games::contains(std::string str)
{
	auto it = std::find(games.begin(), games.end(), str);
	if (it != games.end())
		return games.end() - it;
	return -1;
}

std::string* Games::findGames(std::string _games)
{
	auto it = std::find(games.begin(), games.end(), _games);
	if (it == games.end())
		return NULL;
	return &*it;
}

const int Games::getSize() const
{
	return games.size();
}

std::ostream& operator<<(std::ostream& os, const Games& g)
{
	for (std::string var : g.games)
	{
		os << var << "\n";
	}
	return os;
}
