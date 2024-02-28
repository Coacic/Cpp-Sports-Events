#ifndef _EVENT_H_
#define _EVENT_H_
#include "Team.h"

class Event {
	std::string date, city, * cup, type, * country, medal, * sport;
	Athlete* athlete;
	Team team;
	char isTeamFlag;

public:
	Event(std::string _date, std::string _city, std::string* _sport, std::string* _cup, std::string _type, std::string* _country, std::string _medal, Athlete* _athlete, Team* _team);
	~Event();
	const std::string& getDate() const;
	const std::string& getCity() const;
	const std::string& getSport() const;
	const std::string& getCountry() const;
	const std::string& getCup() const;
	const std::string& getMedal() const;
	const Athlete* getAthlete() const;
	const Team& getTeam() const;
	const bool isTeam() const;
	void parseCompetitor();
	friend std::ostream& operator<<(std::ostream& os, const Event& eve);
};

#endif // !_EVENT_H_