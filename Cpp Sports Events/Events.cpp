#include "Events.h"

Events::Events(int n)
{
	events.reserve(n);
	eventsMu1.reserve(n / 4);
	eventsMu2.reserve(n / 4);
	eventsMu3.reserve(n / 4);
	eventsMu4.reserve(n / 4);
}

Events::~Events()
{
	for_each(events.begin(), events.end(), [&](Event& x) {x.~Event(); });
	for_each(eventsMu1.begin(), eventsMu1.end(), [&](Event& x) {x.~Event(); });
	for_each(eventsMu2.begin(), eventsMu2.end(), [&](Event& x) {x.~Event(); });
	for_each(eventsMu3.begin(), eventsMu3.end(), [&](Event& x) {x.~Event(); });
	for_each(eventsMu4.begin(), eventsMu4.end(), [&](Event& x) {x.~Event(); });
	events.~vector();
	eventsMu1.~vector();
	eventsMu2.~vector();
	eventsMu3.~vector();
	eventsMu4.~vector();
}

void Events::readEventMu(const std::string str, std::unique_ptr<Athletes>& listOfAthletes, std::unique_ptr<Countries>& listOfCountries, std::unique_ptr<Sports>& sports, std::unique_ptr<Games>& games, int i)
{
	std::stringstream ids;
	std::string* country = nullptr;
	std::string* sport = nullptr;
	std::vector<int> listOfAthleteIds;
	int index;
	Athlete* ath = nullptr;
	std::regex rgx("([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!(\\w*)");
	std::regex rgx2("(\\d+)");
	std::smatch match;
	try {
		if (std::regex_search(str.begin(), str.end(), match, rgx))
		{
			Team* teamOfPlayersList = new Team(match[3]);
			if (match[5].str() == "Individual")
			{
				int id = std::stoi(match[7]);
				ath = &listOfAthletes->findById(id);
				teamOfPlayersList->~Team();
				teamOfPlayersList = nullptr;
			}
			else if (match[5].str() == "Team")
			{
				std::string word(match[7]);
				auto words_begin = std::sregex_iterator(word.begin(), word.end(), rgx2);
				auto words_end = std::sregex_iterator();
				for (std::sregex_iterator i = words_begin; i != words_end; ++i)
				{
					std::smatch match = *i;
					std::string match_str = match.str();
					if (!match_str.empty() && std::find_if(match_str.begin(), match_str.end(), [](unsigned char c) { return !std::isdigit(c); }) == match_str.end())
						teamOfPlayersList->pushAthlete(listOfAthletes->findById(std::stoi(match_str)));
				}
				//parseTeam(match[7].str(), &listOfAthleteIds);
				//for (auto it2 = listOfAthleteIds.begin(); it2 != listOfAthleteIds.end(); it2++)
				//{
				//	ath = &listOfAthletes->findById(*it2);
				//	//itAth = std::find_if(listOfAthletes.begin(), listOfAthletes.end(), [&num](Athlete* x) { return x->getId() == num; });
				//	teamOfPlayersList->pushAthlete(*ath);
				//}
				ath = nullptr;
				//teamOfPlayersList->pushAthlete(*(*listOfAthletes).findById(std::stoi(match_str)));
			}
			country = &(*listOfCountries->findCountry(match[6]));
			if (!country) {
				listOfCountries->pushCountry(match[6]);
				country = &(*listOfCountries->findCountry(match[6]));
			}
			sport = &(*sports->findSport(match[3]));
			if (!sport) {
				sports->pushSport(match[3]);
				sport = &(*sports->findSport(match[3]));
			}
			if ((index = games->contains(match[4].str()) == -1))
				index = games->push(match[4]);
			//if (match.suffix() == '\n')
			//	match.suffix().str().clear();
			//Medal* medal = match.suffix();
			//Event* eve = new Event(match[1], match[2], sport, *games.getGames(index), match[5], country, match.suffix(), ath, teamOfPlayersList);
			switch (i)
			{
			case 0:
				eventsMu1.emplace_back(match[1], match[2], sport, games->findGames(match[4]), match[5], country, match[8], ath, teamOfPlayersList);
				break;
			case 1:
				eventsMu2.emplace_back(match[1], match[2], sport, games->findGames(match[4]), match[5], country, match[8], ath, teamOfPlayersList);
				break;
			case 2:
				eventsMu3.emplace_back(match[1], match[2], sport, games->findGames(match[4]), match[5], country, match[8], ath, teamOfPlayersList);
				break;
			case 3:
				eventsMu4.emplace_back(match[1], match[2], sport, games->findGames(match[4]), match[5], country, match[8], ath, teamOfPlayersList);
				break;
			}
			//events.emplace_back(*new Event(match[1], match[2], sport, games->findGames(match[4]), match[5], country, match[8], ath, teamOfPlayersList));
			//new Event(match[1].str(), match[2].str(), sport, games.getGames(index), match[5].str(), country, match.suffix(), ath, teamOfPlayersList)
			//std::string _date, std::string _city, Sports* _sport, std::string _cup, std::string _type, std::string* country, std::string* _medal, Athlete* _athlete, Team* _team
		}
	}
	catch (std::exception e)
	{
		std::cout << "\nError : \n" << e.what() << std::endl;
	}
	//}
	//catch (std::exception e)
	//{
	//	return;
	//}
}

int Events::getCountHowManyRewardsForDifferentSports()
{
	std::string country;
	int n = 0, type = -1;
	std::vector<int> flags(events.size(), 0);
	std::vector<std::string> vect;
	std::vector<Event>::iterator it;
	std::vector<int>::iterator it2 = flags.begin();
	std::cout << "Unesite datu drzavu:" << std::endl;
	std::cin >> country;
	for_each(events.begin(), events.end(), [&it2, &country](Event const& p)
		{
			if (p.getCountry() != country || p.getMedal().empty())
				*it2 = 1;
			it2++;
		});
	it2 = flags.begin();
	for_each(events.begin(), events.end(), [&vect, &it2](Event const& p)
		{
			if (std::find(vect.begin(), vect.end(), p.getSport()) == vect.end() && *it2 == 0)
				vect.push_back(p.getSport());
			it2++;
		});
	return (int)vect.size();
}

std::vector<std::string> Events::getCountriesThatHaveGoldMedal()
{
	std::vector<std::string> countries;
	std::string country;
	std::cin >> country;
	for_each(events.begin(), events.end(), [&countries](Event const& p)
		{
			if (p.getMedal() == "Gold" && std::find(countries.begin(), countries.end(), p.getCountry()) == countries.end())
				countries.push_back(p.getCountry());
		});
	return countries;
}

std::vector<std::string> Events::getCitiesThatHostedOlympicsAtLeastOnce()
{
	std::vector<std::string> cities;
	std::string country;
	std::cin >> country;
	for_each(events.begin(), events.end(), [&cities](Event const& p)
		{
			if (std::find(cities.begin(), cities.end(), p.getCountry()) == cities.end())
				cities.push_back(p.getCountry());
		});
	return cities;
}

std::vector<Athlete> Events::getAllTheAthletesThatCompetedInPairOfGames(std::unique_ptr<Athletes>& athletes, std::unique_ptr<Games>& games)
{
	std::vector<Athlete> vector;
	std::vector<Athlete>::iterator it;
	std::string game1, game2;
	std::cout << "Unesite par igara:\n";
	std::cin >> game1 >> game2;
	for_each(events.begin(), events.end(), [&](Event const& p1)
		{
			for_each(events.begin(), events.end(), [&](Event const& p2)
				{
					if (!p1.isTeam())
						if (p1.getCup() == game1 && p2.getCup() == game2 && ((std::find(vector.begin(), vector.end(), *p1.getAthlete())) == vector.end()))
								vector.push_back(*(p1.getAthlete()));
				});
		});
	return vector;
}

std::vector<std::pair<std::string, Athlete>> Events::getPairOfCountryAthleteThatWonAtLeastOneMedalInTeamAndIndividual(std::unique_ptr<Athletes>& athletes)
{
	std::vector<std::pair<std::string, Athlete>> parovi;
	for_each(events.begin(), events.end(), [&](Event& p1)
		{
			if (!p1.getMedal().empty()) {
				if (!p1.isTeam()) {
					for_each(events.begin(), events.end(), [&](Event& p2)
						{
							if (p2.isTeam() && !p2.getMedal().empty() && p2.getTeam().containsAthlete(*p1.getAthlete()))
							{
								std::pair<std::string, Athlete> p;
								p.first = p2.getCountry(); p.second = *p2.getAthlete();
								if (std::find(parovi.begin(), parovi.end(), p) == parovi.end())
									parovi.push_back(p);
							}
						});
				}
			}
		});
	return parovi;
}

std::vector<std::string> Events::findTenYoungestAthletesWithMedalsFirstOccurence(Athlete* athletes)
{
	std::vector<Athlete> vect;
	std::vector<int> flags(events.size(), 0);
	std::vector<Event>::iterator it;
	std::vector<int>::iterator it2 = flags.begin();
	for_each(events.begin(), events.end(), [&vect, &it2](Event const& p)
		{
			if (p.getMedal().empty())
				*it2 = 1;
		});
	//if (std::find(vect.begin(), vect.end(), p.getCountry()) == vect.end())
	//	vect.push_back(*p.getAthlete());
	std::vector<std::string> s;
	return s;
}

std::vector<std::string> Events::getThreeBestCountries(Athlete* athletes)
{
	std::string season, year;
	std::cin >> year >> season;
	std::vector<Athlete> vect;
	std::vector<int> flags(events.size(), 0);
	std::vector<Event>::iterator it;
	std::vector<int>::iterator it2 = flags.begin();
	for_each(events.begin(), events.end(), [&vect, &it2](Event const& p)
		{
			if (p.getMedal().empty())
				*it2 = 1;
		});
	std::vector<std::string> s;
	return s;
}

void Events::readEventsMu(std::vector<std::string>& vecFileEve, std::unique_ptr<Athletes>& athletes, std::unique_ptr<Countries>& countries, std::unique_ptr<Sports>& sports, std::unique_ptr<Games>& games, int i)
{
	//std::vector<std::string> vecFileAth, int i
	std::vector<std::string>::iterator it;
	for (it = vecFileEve.begin(); it != vecFileEve.end(); it++)
		readEventMu(*it, athletes, countries, sports, games, i);
}

int Events::getCountOfCompetitors(std::unique_ptr<Countries>& countries, std::unique_ptr<Sports>& sports)
{
	std::vector<char> flags(filterData(countries, sports));
	int n = 0;
	std::vector<char>::iterator it = flags.begin();
	for (auto const& x : events)
	{
		if (x.getAthlete() && *it == 0)
		{
			n++;
		}
		else if (*it == 0)
		{
			n += x.getTeam().getSize();
		}
		it++;
	}
	return n;
}

int Events::getNumberOfDifferentSports(std::unique_ptr<Countries>& countries, std::unique_ptr<Sports>& sports)
{
	std::vector<char> flags(filterData(countries, sports));
	std::vector<std::string> vect;
	std::vector<std::string>::iterator vectIt;
	int n = 0;
	std::vector<char>::iterator it2 = flags.begin();
	for (auto const& x : events)
	{
		if ((vectIt = std::find(vect.begin(), vect.end(), x.getSport())) == vect.end()) {
			vect.push_back(x.getSport());
			it2++;
		}
	}
	return (int)vect.size();
}

int Events::getAverageWeightOfAllCompetitors(std::unique_ptr<Countries>& countries, std::unique_ptr<Sports>& sports)
{
	std::vector<char> flags(filterData(countries, sports));
	int n = 0, weight = 0, count = 0;
	std::vector<char>::iterator it = flags.begin();
	for (const Event& x : events)
	{
		if (*it == 0 && (x.getAthlete() != nullptr)) {
			if (x.getAthlete()->getWeight() == "NA" || x.getAthlete()->getWeight().empty()) {}
			else
			{
				weight += std::stoi(x.getAthlete()->getWeight());
				count++;
			}
		}
		else if (*it == 0) {
			for (int i = 0; i < x.getTeam().getSize(); i++)
			{
				if (x.getTeam().getAthlete(i).getWeight() != "NA") {
					weight += std::stoi(x.getTeam().getAthlete(i).getWeight());
					count++;
				}
			}
		}
		it++;
	}
	if (count == 0)
		return 0;
	return weight / count;
}

int Events::getSize()
{
	return (int)events.size();
}

const Event Events::getEvent(int i) const
{
	auto itEnd = events.begin();
	if (i > events.size())
		return *events.end();
	std::advance(itEnd, i);
	return *itEnd;
}

bool compareTeam(Team i1, Team i2)
{
	return (i1.getSize() < i2.getSize());
}

bool compareSports(Team i1, Team i2)
{
	return (i1.getSport() < i2.getSport());
}

bool compareGames(std::string i1, std::string i2)
{
	return (i1 < i2);
}

std::vector<Team> Events::getTeamsForGivenCountryAndGames(std::unique_ptr<Countries>& countries, std::unique_ptr<Games>& games)
{
	std::string country, game;
	std::vector<Team> timovi;
	std::cout << "Unesite zadatu drzavu i zadate igre sa razmakom:" << std::endl;
	std::cin >> country >> game;
	auto it = events.begin();
	while ((it = std::find_if(it, events.end(), [&country](Event& e) { return (e.isTeam() && !country.compare(e.getCountry())); })) != events.end())
	{
		Team t = *new Team();
		for (size_t i = 0; i < it->getTeam().getSize(); i++)
			t.pushAthlete(it->getTeam().getAthlete((int)i));
		timovi.push_back(t);
		it++;
	}
	std::sort(timovi.begin(), timovi.end(), compareTeam);
	std::sort(timovi.begin(), timovi.end(), compareSports);
	return timovi;
}

int Events::getAverageHeightOfAllCompetitors(std::unique_ptr<Countries>& countries, std::unique_ptr<Sports>& sports)
{
	std::vector<char> flags(filterData(countries, sports));
	int n = 0, height = 0, count = 0;
	std::vector<char>::iterator it = flags.begin();
	const Team* team = nullptr;
	for (const Event& x : events)
	{
		if (*it == 0 && x.getAthlete()) {
			if (x.getAthlete()->getHeight() != "NA" || x.getAthlete()->getHeight().empty()) {
				height += std::stoi(x.getAthlete()->getHeight());
				count++;
			}
		}
		else if (*it == 0) {
			for (int i = 0; i < x.getTeam().getSize(); i++)
			{
				if (x.getTeam().getAthlete(i).getHeight() != "NA" || x.getTeam().getAthlete(i).getHeight().empty()) {
					height += std::stoi(x.getTeam().getAthlete(i).getHeight());
					count++;
				}
			}
		}
		it++;
	}
	if (count == 0)
		return 0;
	return (int)height/count;
}

void Events::combineMu()
{
	events.insert(std::end(events), std::begin(eventsMu1), std::end(eventsMu1));
	events.insert(std::end(events), std::begin(eventsMu2), std::end(eventsMu2));
	events.insert(std::end(events), std::begin(eventsMu3), std::end(eventsMu3));
	events.insert(std::end(events), std::begin(eventsMu4), std::end(eventsMu4));
}

std::vector<char> Events::filterData(std::unique_ptr<Countries>& countries, std::unique_ptr<Sports>& sports)
{
	std::vector<char> flags(events.size(), 0);
	std::vector<char>::iterator it = flags.begin();
	std::string input, sport, country, year, date, medal;
	int n = 0, wrongInput = 0, type = -1;
	while (1) {
		wrongInput = 0;
		std::cout << "\nUnesite kombinaciju brojeva za odrednjene filtere koje zelite:\n0 - Ni jedan\n1 - Filter na osnovu sporta\n2 - Filter na osnovu drzave\n3 - Filter na osnovu godine olimpijskih igara\n4 - Filter na osnovu da li je tim ili sam atleta\n5 - Filter na osnovu medalja\n\n";
		std::cin >> input;
		char* p;
		long converted = strtol(input.c_str(), &p, 10);
		while (*p) {
			std::cout << "Unesite brojcane vrednosti!" << std::endl;
			std::cin >> input;
			converted = strtol(input.c_str(), &p, 10);
		}
		while (!input.empty())
		{
			n = input.front() - '0';
			input.erase(0, 1);
			it = flags.begin();
			switch (n)
			{
			case 0:
				break;

			case 1:
				std::cout << "Unesite filter na osnovu sporta: \n";
				std::cin >> sport;
				if (!sports->findSport(sport)) {
					std::cout << "Unesite validan sport" << std::endl;
					wrongInput = 1;
				}
				for_each(events.begin(), events.end(), [&it, &sport](Event const& p)
					{
						if (p.getSport() != sport)
							*it = 1;
						it++;
					});
				break;

			case 2:
				std::cout << "Unesite filter na osnovu drzave: \n";
				std::cin >> country;
				if (!countries->findCountry(country)) {
					std::cout << "Unesite validnu drzavu" << std::endl;
					wrongInput = 1;
				}
				for_each(events.begin(), events.end(), [&it, &country](Event const& p)
					{
						if (p.getCountry() != country)
							*it = 1;
						it++;
					});
				break;

			case 3:
				std::cout << "Unesite filter na osnovu godine odrzavanje olimpijske igre: \n";
				std::cin >> year;
				converted = strtol(year.c_str(), &p, 10);
				if (*p) {
					std::cout << "\nUnesite cifre za filter za godine!" << std::endl;
					wrongInput = 1;
				}
				for_each(events.begin(), events.end(), [&it, &year](Event const& p)
					{
						if (p.getDate().find(year))
							*it = 1;
						it++;
					});
				break;

			case 4:
				std::cout << "\nUnesite filter na osnovu da li je tim ili atleta\n0 - Individualni\n1 - Team\n";
				std::cin >> type;
				if (type == 0)
					for_each(events.begin(), events.end(), [&it, &type](Event const& p)
						{
							if (!p.getAthlete())
								*it = 1;
							it++;
						});
				else
					for_each(events.begin(), events.end(), [&it, &type](Event const& p)
						{
							if (p.getAthlete())
								*it = 1;
							it++;
						});
				break;

			case 5:
				std::cout << "\nUnesite filter na osnovu tipe medalje, Gold, Silver, Bronze ili bez medalje \"!\"\n";
				std::cin >> medal;
				if (medal == "Gold" || medal == "Silver" || medal == "Bronze" || medal == "!") {
					if (medal == "!")
						for_each(events.begin(), events.end(), [&it, &medal](Event const& p)
							{
								if (!p.getMedal().empty())
									*it = 1;
								it++;
							});
					else
						for_each(events.begin(), events.end(), [&it, &medal](Event const& p)
							{
								if (p.getMedal() != medal)
									*it = 1;
								it++;
							});
				}
				else {
					std::cout << "Unesite validne filtere medalja" << std::endl;
					wrongInput = 1;
				}
				break;

			default:
				std::cout << "Niste uneli filter koji postoji!" << std::endl;
				break;
			}
			if (input.empty() && wrongInput == 0)
				return flags;
			if (wrongInput)
				break;
		}
	}
}

std::ostream& operator<<(std::ostream& stream, const Events& eve)
{
	auto it = eve.events.begin();
	for (it; it != eve.events.end(); it++)
	{
		stream << *it << std::endl;
	}
	return stream;
}