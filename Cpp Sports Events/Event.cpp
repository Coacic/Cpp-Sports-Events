#include "Event.h"

Event::Event(std::string _date, std::string _city, std::string* _sport, std::string* _cup, std::string _type, std::string* _country, std::string _medal, Athlete* _athlete, Team* _team)
{
	date = _date;
	city = _city;
	cup = _cup;
	type = _type;
	medal = _medal;
	athlete = _athlete;
	team = NULL;
	isTeamFlag = 0;
	if (_team)
	{
		team = *new Team(*_team);
		isTeamFlag = 1;
	}
	country = _country;
	sport = _sport;
};

Event::~Event()
{
	if (athlete != nullptr)
		athlete->~Athlete();
	team.~Team();
}

const std::string& Event::getDate() const
{
	return date;
}

const std::string& Event::getCity() const
{
	return city;
}

const std::string& Event::getSport() const
{
	return *sport;
}

const std::string& Event::getCup() const
{
	return *cup;
}

const std::string& Event::getCountry() const
{
	return *country;
}

const std::string& Event::getMedal() const
{
	return medal;
}

const Athlete* Event::getAthlete() const
{
	return athlete;
}

const Team& Event::getTeam() const
{
	return team;
}

const bool Event::isTeam() const
{
	if (isTeamFlag == 1)
		return true;
	return false;
}

void Event::parseCompetitor()
{
}

std::ostream& operator<<(std::ostream& os, const Event& e)
{
	if (&(e.getTeam()) != nullptr)
	{
		os << "(*)Tim:\n" << e.getTeam();
		if (e.getAthlete())
			os << e.getAthlete();
		os << e.getDate() << " " << e.getCity() << " " << e.getSport() << " " << e.getCup() << " " << e.getCountry() << " " << e.getMedal();
	}
	else if (e.getAthlete())
	{
		os << "(-)Atleta: " << *e.getAthlete() << " " << e.getDate() << " " << e.getCity() << " " << e.getSport()
			<< " " << e.getCup() << " " << e.getCountry() << " " << e.getMedal();

	}
	return os;
}