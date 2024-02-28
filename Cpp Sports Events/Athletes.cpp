#include "Athletes.h"

std::mutex athLock;

Athletes::Athletes(int size)
{
	athletes.reserve(size);
}

Athletes::~Athletes()
{
	for_each(athletes.begin(), athletes.end(), [&](Athlete& x) {x.~Athlete(); });
	for_each(muAth1.begin(), muAth1.end(), [&](Athlete& x) {x.~Athlete(); });
	for_each(muAth2.begin(), muAth2.end(), [&](Athlete& x) {x.~Athlete(); });
	for_each(muAth3.begin(), muAth3.end(), [&](Athlete& x) {x.~Athlete(); });
	for_each(muAth4.begin(), muAth4.end(), [&](Athlete& x) {x.~Athlete(); });
	athletes.~vector();
	muAth1.~vector();
	muAth2.~vector();
	muAth3.~vector();
	muAth4.~vector();
}

void Athletes::readAthlete(const std::string str)
{

	std::lock_guard<std::mutex> guard(athLock);
	std::regex rgx("([0-9]*)!([^!]*)!(NA|[MF])!([^!])!([^!])!([^!])");
	std::smatch match;
	if (std::regex_search(str.begin(), str.end(), match, rgx))
		athletes.emplace_back(*new Athlete(std::stoi(match[1]), match[4], match[6], match[5], match[2], match[3].str()));
}

void Athletes::readAthleteMu(const std::string str, std::vector<Athlete>& vec)

{
	//std::lock_guard<std::mutex> guard(athLock);
	std::regex rgx("([0-9]*)!([^!]*)!(NA|[MF])!([^!]*)!([^!]*)!([^\n]*)");
	std::smatch match;
		if (std::regex_search(str.begin(), str.end(), match, rgx))
			vec.emplace_back(std::stoi(match[1]), match[4], match[6], match[5], match[2], match[3].str());
	//if (std::regex_search(str.begin(), str.end(), match, rgx))
	//	athletes.emplace_back(*new Athlete(std::stoi(match[1]), match[4], match[6], match[5], match[2], match[3].str()));
}

void Athletes::readAthletesMu(std::vector<std::string> vecFileAth, int i)
{
	std::vector<std::string>::iterator it;
	switch (i)
	{
	case 0:
		for (it = vecFileAth.begin(); it != vecFileAth.end(); it++)
			readAthleteMu(*it, muAth1);
	break;

	case 1:
		for (it = vecFileAth.begin(); it != vecFileAth.end(); it++)
			readAthleteMu(*it, muAth2);
		break;

	case 2:
		for (it = vecFileAth.begin(); it != vecFileAth.end(); it++)
			readAthleteMu(*it, muAth3);
		break;

	case 3:
		for (it = vecFileAth.begin(); it != vecFileAth.end(); it++)
			readAthleteMu(*it, muAth4);
		break;

	default:
		break;
	}
}

Athlete Athletes::getAthlete(int i) const
{
	auto itEnd = athletes.begin();
	if (i > athletes.size())
		return *athletes.end();
	std::advance(itEnd, i);
	return *itEnd;
}

int Athletes::getSize()
{
	return athletes.size();
}

void Athletes::combineMu()
{
	athletes.insert(std::end(athletes), std::begin(muAth1), std::end(muAth1));
	athletes.insert(std::end(athletes), std::begin(muAth2), std::end(muAth2));
	athletes.insert(std::end(athletes), std::begin(muAth3), std::end(muAth3));
	athletes.insert(std::end(athletes), std::begin(muAth4), std::end(muAth4));
}

Athlete& Athletes::findById(int id)
{
	std::vector<Athlete>::iterator itAth = std::find_if(athletes.begin(), athletes.end(), [&id](Athlete x) { return x.getId() == id; });
	auto* it = itAth._Ptr;
	return *itAth;
}

std::vector<Athlete> Athletes::findTheListOfYoungestAthletes(int n)
{
	std::vector<Athlete> athl;
	std::vector<Athlete>::iterator athlIt = athletes.begin();
	Athlete* athlete = nullptr;
	athl.reserve((n + 1));
	if (n <= 0)
		return athl;
	//for (int i = 0; i < n; i++)
	//{
	//	//athlete = &this->getAthlete(i);
	//	athlIt = std::min_element(athletes.begin(), athletes.end());
	//	athlete = &*athlIt;
	//	athl.emplace_back(athlete);
	//}
	//for (int i = 0; i < n; i++)
	//{
	//	athlIt = athl.begin();
	//}
	return athl;
}

std::ostream& operator<<(std::ostream& stream, const Athletes& ath)
{
	auto it = ath.athletes.begin();
	for (it; it != ath.athletes.end(); it++)
	{
		stream << *it << std::endl;
	}
	return stream;
}
