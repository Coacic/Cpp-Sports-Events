#include "Team.h"

Team::Team()
{
}

Team::Team(int r)
{
	team.reserve(r);
}

Team::Team(std::string s)
{
	sport = s;
}

Team::Team(const Team&t)
{
	for (int i = 0; i < t.getSize(); i++)
	{
		pushAthlete(t.getAthlete(i));
	}
	sport = t.getSport();
}

Team::~Team()
{
	for_each(team.begin(), team.end(), [](Athlete a) {a.~Athlete(); });
	team.~vector();
}

const std::string& Team::getSport() const
{
	return sport;
}

void Team::pushAthlete(Athlete ath)
{
	team.emplace_back(ath);
}

const int Team::getSize() const
{
	return static_cast<int>(team.size());
}

const Athlete& Team::operator[](int index) const
{
	if (index >= team.size()) {
		std::cout << "Error : Niz tima van opsega";
		exit(0);
	}
	return team[index];
}

const Athlete& Team::getAthlete(int i) const
{
	auto iter = team.begin();
	std::advance(iter, i);
	return *iter;
}

const bool Team::containsAthlete(Athlete const & ath) const
{
	auto it = find(team.begin(), team.end(), ath);
	if (it != team.end())
		return true;
	return false;
}

std::ostream& operator<<(std::ostream& os, const Team& a)
{
	for (int i = 0; i < a.getSize(); i++)
	{
		os << a.team[i] << std::endl;
	}
	return os;
}