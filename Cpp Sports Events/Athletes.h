#ifndef _ATHLETES_H_
#define _ATHLETES_H_
#include "Athlete.h"

class Athletes
{
	std::vector<Athlete> athletes;
	std::vector<Athlete> muAth1;
	std::vector<Athlete> muAth2;
	std::vector<Athlete> muAth3;
	std::vector<Athlete> muAth4;

public:
	Athletes(int);
	Athletes() {};
	~Athletes();
	void readAthlete(const std::string str);
	void readAthleteMu(const std::string str, std::vector<Athlete>&);
	void readAthletesMu(std::vector<std::string>, int);
	Athlete getAthlete(int i) const;
	int getSize();
	void combineMu();
	Athlete& findById(int id);
	std::vector<Athlete> findTheListOfYoungestAthletes(int);
	friend std::ostream& operator<<(std::ostream& stream, const Athletes& ath);
};


#endif // !_ATHLETES_H_
