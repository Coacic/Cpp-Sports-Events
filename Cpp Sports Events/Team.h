#ifndef _TEAM_H_
#define _TEAM_H_
#include "Athletes.h"

class Team : public Competitor{
	std::vector<Athlete> team;
	std::string sport;
public:
	Team();
	Team(int r);
	Team(std::string s);
	Team(const Team&);
	~Team();
	const std::string& getSport() const;
	void pushAthlete(Athlete ath);
	const int getSize() const;
	const Athlete& getAthlete(int i) const;
	const bool containsAthlete(const Athlete&) const;
	friend std::ostream& operator<<(std::ostream& os, const Team& a);
	void parseCompetitor() {};
	const Athlete& operator[](int index) const;
};

#endif // !_TEAM_H_

