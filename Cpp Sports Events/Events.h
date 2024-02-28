#ifndef _EVENTS_H_
#define _EVENTS_H_
#include "Event.h"

class Events {
	std::vector<Event> events;
	std::vector<Event> eventsMu1;
	std::vector<Event> eventsMu2;
	std::vector<Event> eventsMu3;
	std::vector<Event> eventsMu4;

public:
	Events(int n);
	~Events();
	//void readEvent(const std::string str, Athletes* listOfAthletes, Countries* listOfCountries, Sports* sports, Games* games);
	const Event getEvent(int i) const;
	int getSize();
	void readEventMu(const std::string str, std::unique_ptr<Athletes>& listOfAthletes, std::unique_ptr<Countries>& listOfCountries, std::unique_ptr<Sports>& sports, std::unique_ptr<Games>& games, int i);
	void readEventsMu(std::vector<std::string>& vecFileEve, std::unique_ptr<Athletes>& listOfAthletes, std::unique_ptr<Countries>& listOfCountries, std::unique_ptr<Sports>& sports, std::unique_ptr<Games>& games, int i);
	void combineMu();
	int getCountOfCompetitors(std::unique_ptr<Countries>& countries, std::unique_ptr<Sports>& sports);
	int getNumberOfDifferentSports(std::unique_ptr<Countries>& countries, std::unique_ptr<Sports>& sports);
	int getAverageHeightOfAllCompetitors(std::unique_ptr<Countries>& countries, std::unique_ptr<Sports>& sports);
	int getAverageWeightOfAllCompetitors(std::unique_ptr<Countries>& countries, std::unique_ptr<Sports>& sports);
	std::vector<char> filterData(std::unique_ptr<Countries>& countries, std::unique_ptr<Sports>& sports);

	std::vector<Team> getTeamsForGivenCountryAndGames(std::unique_ptr<Countries>& countries, std::unique_ptr<Games>& games);
	int getCountHowManyRewardsForDifferentSports();
	std::vector<std::string> getCountriesThatHaveGoldMedal();
	std::vector<std::string> getCitiesThatHostedOlympicsAtLeastOnce();
	std::vector<Athlete> getAllTheAthletesThatCompetedInPairOfGames(std::unique_ptr<Athletes>& athletes, std::unique_ptr<Games>& games);
	std::vector<std::pair<std::string, Athlete>> getPairOfCountryAthleteThatWonAtLeastOneMedalInTeamAndIndividual(std::unique_ptr<Athletes>& athletes);

	std::vector<std::string> getThreeBestCountries(Athlete * athletes);
	std::vector<std::string> findTenYoungestAthletesWithMedalsFirstOccurence(Athlete * athletes);

	friend std::ostream& operator<<(std::ostream& stream, const Events& eve);
};

#endif // !_EVENTS_H_