#ifndef _ATHLETE_H_
#define _ATHLETE_H_
#include "Competitor.h"

class Athlete : public Competitor{
	int id;
	std::string name, weight, height, age;
	char gender;

public:
	Athlete(int, std::string, std::string, std::string, std::string, std::string);
	Athlete();
	Athlete(const Athlete& ath);
	~Athlete();
	const int getId() const;
	const std::string& getAge() const;
	const std::string& getWeight() const;
	const std::string& getHeight() const;
	const std::string& getName() const;
	const char& getGender() const;
	friend std::ostream& operator<< (std::ostream& stream, const Athlete& athlete);
	void parseCompetitor();
	bool operator<(const Athlete& ath) const;
	bool operator==(const Athlete& ath) const;

};

#endif // !_ATHLETE_H_