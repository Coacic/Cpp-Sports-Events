#define _CRT_SECURE_NO_WARNINGS
#include "Medals.h"

int debugLevel = 0;

int main()
{
	int isDataLoaded1 = 0, isDataLoaded2 = 0, n = 0, count = 0;
	FILE* fileEveC = fopen("C:\\Users\\Coca\\source\\repos\\Cpp Sports Events\\Cpp Sports Events\\events.txt", "r");
	FILE* fileAthC = fopen("C:\\Users\\Coca\\source\\repos\\Cpp Sports Events\\Cpp Sports Events\\athletes.txt", "r");
	std::ofstream out("C:\\Users\\Coca\\source\\repos\\Cpp Sports Events\\Cpp Sports Events\\out.txt");
	int linesAth = 0;
	int linesEve = 0;
	char bufferInAthC[1024];
	char bufferInEveC[1024];
	std::string line;
	std::string bufferInAth;
	std::string op;
	std::chrono::high_resolution_clock::time_point begin;
	std::chrono::high_resolution_clock::time_point end;
	while (fgets(bufferInAthC, sizeof bufferInAthC, fileAthC))
		linesAth++;
	while (fgets(bufferInEveC, sizeof bufferInEveC, fileEveC))
		linesEve++;
	fseek(fileAthC, 0, SEEK_SET);
	fseek(fileEveC, 0, SEEK_SET);
	std::string buff;
	std::vector<std::thread> threads; threads.reserve(4);
	std::vector<std::string> vecFileAth; vecFileAth.reserve((linesAth / 4 + 1));
	std::vector<std::string> vecFileAth2; vecFileAth2.reserve((linesAth / 4 + 1));
	std::vector<std::string> vecFileAth3; vecFileAth3.reserve((linesAth / 4 + 1));
	std::vector<std::string> vecFileAth4; vecFileAth4.reserve((linesAth / 4 + 1));
	std::vector<std::string> vecFileEve; vecFileEve.reserve((linesEve / 4 + 1));
	std::vector<std::string> vecFileEve2; vecFileEve2.reserve((linesEve / 4 + 1));
	std::vector<std::string> vecFileEve3; vecFileEve3.reserve((linesEve / 4 + 1));
	std::vector<std::string> vecFileEve4; vecFileEve4.reserve((linesEve / 4 + 1));
	std::vector<std::string> vector;
	std::vector<Team> vectorTimova;
	std::vector<Athlete> vectorAthleta;
	std::vector<std::pair<std::string, Athlete>> parovi;
	std::vector<std::string>::iterator it;

	//Potrebne stvari:
	std::unique_ptr<Games> games(new Games());
	std::unique_ptr<Athletes> athletes(new Athletes((linesAth + 1)));
	std::unique_ptr<Events> events(new Events((linesEve + 1)));
	std::unique_ptr<Countries> countries(new Countries());
	std::unique_ptr<Sports> sports(new Sports());
	try {
		while (1) {
			//14 7 8 ne radi
			std::cout << "\n-----------------------------------------------------------------------------------------------------------------------\nUnesite opciju:\n0. Exit\n1. Unos podataka\n2. Ispis podataka atleta\n3. Ucitavanje podataka eventova\n4. Ispis podataka eventova";
			std::cout << "\n5. Ukupan broj ucesnika na olimpijskim igrama\n6. Ukupan broj razlicitih disciplina na Olimpijskim igrama\n7. Srednja vrednost visine svih takmicara\n8. Srednja vrednost tezine svih takmicara";
			std::cout << "\n9. Odredjivanje broja razlicitih sportova u kojima je zadata drzava osvojila barem jednu medalju\n10. Odredjivanje drzava koje su na barem jednim Olimpijskim igrama ostvarile najbolji uspeh\n11. Odredjivanje svih gradova u kojima su olimpijske igre odrzane barem jednom";
			std::cout << "\n12. Dohvatanje svih timova koje je zadata drzava imala na zadatim igrama\n13. Odredjivanje svih sportista koji su ucestvovali na zadatom paru Olimpijskih igara\n14. Dohvatanje svih parova drzava - sportista";
			std::cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
			std::cin >> op;
			char* p;
			long converted = strtol(op.c_str(), &p, 10);
			while (*p) {
				std::cout << "Unesite brojnu vrednost za opcije!" << std::endl;
				std::cin >> op;
				converted = strtol(op.c_str(), &p, 10);
			}
			switch (std::stoi(op))
			{
			case 0:
				events->~Events();
				athletes->~Athletes();
				games->~Games();
				countries->~Countries();
				sports->~Sports();
				fclose(fileEveC); fclose(fileAthC);
				std::cout << "Program uspesno zavrsen\n";
				exit(0);

			case 1:
				std::cout << "Unos podataka je u toku za athlete";
				while (fgets(bufferInAthC, sizeof bufferInAthC, fileAthC) != NULL)
				{
					vecFileAth.emplace_back(bufferInAthC);
					if (fgets(bufferInAthC, sizeof bufferInAthC, fileAthC) == NULL)
						break;
					vecFileAth2.emplace_back(bufferInAthC);
					if (fgets(bufferInAthC, sizeof bufferInAthC, fileAthC) == NULL)
						break;
					vecFileAth3.emplace_back(bufferInAthC);
					if (fgets(bufferInAthC, sizeof bufferInAthC, fileAthC) == NULL)
						break;
					vecFileAth4.emplace_back(bufferInAthC);
				}
				begin = std::chrono::high_resolution_clock::now();
				threads.push_back(std::thread(&Athletes::readAthletesMu, &(*athletes), vecFileAth, 0));
				threads.push_back(std::thread(&Athletes::readAthletesMu, &(*athletes), vecFileAth2, 1));
				threads.push_back(std::thread(&Athletes::readAthletesMu, &(*athletes), vecFileAth3, 2));
				threads.push_back(std::thread(&Athletes::readAthletesMu, &(*athletes), vecFileAth4, 3));
				for (std::thread& t : threads)
					if (t.joinable())
						t.join();
				for (std::thread& t : threads)
					threads.pop_back();
				athletes->combineMu();
				std::cout << "\nPodaci uspesno ucitani!";
				isDataLoaded1 = 1;
				end = std::chrono::high_resolution_clock::now();
				std::cout << "\nIzvrsena komanda za = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "." << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << std::endl;
				break;
			case 2:
				if (!isDataLoaded1)
				{
					std::cout << "Unesite podatke atleta prvo!";
					break;
				}
				begin = std::chrono::high_resolution_clock::now();
				std::cout << "Unesite koliko linija zelite da se istampa:\nProizvoljan negativan broj za ispis svih takmicara:\n";
				std::cin >> n;
				if (n <= 0)
					n = athletes->getSize();
				for (int i = 0; i < n; i++)
					std::cout << athletes->getAthlete(i) << std::endl;
				count = 0;
				end = std::chrono::high_resolution_clock::now();
				std::cout << "\nIzvrsena komanda za = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "." << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << std::endl;
				break;

			case 3:
				if (!isDataLoaded1)
				{
					std::cout << "Unesite podatke atleta prvo!";
					break;
				}
				std::cout << "Unos podataka je u toku za eventove";
				begin = std::chrono::high_resolution_clock::now();
				while (fgets(bufferInEveC, sizeof bufferInEveC, fileEveC) != NULL)
				{
					vecFileEve.push_back(bufferInEveC);
					if (fgets(bufferInEveC, sizeof bufferInEveC, fileEveC) == NULL)
						break;
					vecFileEve2.push_back(bufferInEveC);
					if (fgets(bufferInEveC, sizeof bufferInEveC, fileEveC) == NULL)
						break;
					vecFileEve3.push_back(bufferInEveC);
					if (fgets(bufferInEveC, sizeof bufferInEveC, fileEveC) == NULL)
						break;
					vecFileEve4.push_back(bufferInEveC);
				}
				threads.push_back(std::thread(&Events::readEventsMu, &*events, std::ref(vecFileEve), std::ref(athletes), std::ref(countries), std::ref(sports), std::ref(games), 0));
				threads.push_back(std::thread(&Events::readEventsMu, &*events, std::ref(vecFileEve2), std::ref(athletes), std::ref(countries), std::ref(sports), std::ref(games), 1));
				threads.push_back(std::thread(&Events::readEventsMu, &*events, std::ref(vecFileEve3), std::ref(athletes), std::ref(countries), std::ref(sports), std::ref(games), 2));
				threads.push_back(std::thread(&Events::readEventsMu, &*events, std::ref(vecFileEve4), std::ref(athletes), std::ref(countries), std::ref(sports), std::ref(games), 3));
				for (std::thread& t : threads)
				{
					if (t.joinable())
						t.join();
				}
				for (std::thread& t : threads)
					threads.pop_back();
				events->combineMu();
				std::cout << "\nPodaci uspesno ucitani";
				isDataLoaded2 = 1;
				end = std::chrono::high_resolution_clock::now();
				std::cout << "\nIzvrsena komanda za = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "." << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << std::endl;
				break;

			case 4:
				if (!isDataLoaded1 || !isDataLoaded2)
				{
					std::cout << "Unesite podatke atleta i eventova prvo!";
					break;
				}
				std::cout << "Unesite koliko linija zelite da se istampa:\nProizvoljan negativan broj za ispis svih takmicara\n";
				begin = std::chrono::high_resolution_clock::now();
				std::cin >> n;
				if (n <= 0)
					n = events->getSize();
				std::cout << events->getSize() << std::endl;
				for (int i = 0; i < n; i++)
					std::cout << events->getEvent(i) << std::endl;
				end = std::chrono::high_resolution_clock::now();
				std::cout << "\nIzvrsena komanda za = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "." << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << std::endl;
				break;

			case 5:
				if (!isDataLoaded1 || !isDataLoaded2)
				{
					std::cout << "Unesite podatke atleta i eventova prvo!";
					break;
				}
				begin = std::chrono::high_resolution_clock::now();
				std::cout << "\n" << events->getCountOfCompetitors(countries, sports);
				end = std::chrono::high_resolution_clock::now();
				std::cout << "\nIzvrsena komanda za = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "." << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << std::endl;
				break;

			case 6:
				if (!isDataLoaded1 || !isDataLoaded2)
				{
					std::cout << "Unesite podatke atleta i eventova prvo!";
					break;
				}
				begin = std::chrono::high_resolution_clock::now();
				std::cout << "\n" << events->getNumberOfDifferentSports(countries, sports);
				end = std::chrono::high_resolution_clock::now();
				std::cout << "\nIzvrsena komanda za = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "." << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << std::endl;
				break;

			case 7:
				if (!isDataLoaded1 || !isDataLoaded2)
				{
					std::cout << "Unesite podatke atleta i eventova prvo!";
					break;
				}
				begin = std::chrono::high_resolution_clock::now();
				std::cout << "\n" << events->getAverageHeightOfAllCompetitors(countries, sports);
				end = std::chrono::high_resolution_clock::now();
				std::cout << "\nIzvrsena komanda za = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "." << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << std::endl;
				break;

			case 8:
				if (!isDataLoaded1 || !isDataLoaded2)
				{
					std::cout << "Unesite podatke atleta i eventova prvo!";
					break;
				}
				begin = std::chrono::high_resolution_clock::now();
				std::cout << events->getAverageWeightOfAllCompetitors(countries, sports);
				end = std::chrono::high_resolution_clock::now();
				std::cout << "\nIzvrsena komanda za = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "." << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << std::endl;

			case 9:
				if (!isDataLoaded1 || !isDataLoaded2)
				{
					std::cout << "Unesite podatke atleta i eventova prvo!";
					break;
				}
				begin = std::chrono::high_resolution_clock::now();
				std::cout << events->getNumberOfDifferentSports(countries, sports);
				end = std::chrono::high_resolution_clock::now();
				std::cout << "\nIzvrsena komanda za = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "." << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << std::endl;
				break;

			case 10:
				if (!isDataLoaded1 || !isDataLoaded2)
				{
					std::cout << "Unesite podatke atleta i eventova prvo!";
					break;
				}
				begin = std::chrono::high_resolution_clock::now();
				vector = events->getCountriesThatHaveGoldMedal();
				for_each(vector.begin(), vector.end(), [](const std::string& x) {std::cout << x << std::endl; });
				end = std::chrono::high_resolution_clock::now();
				std::cout << "\nIzvrsena komanda za = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "." << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << std::endl;
				break;

			case 11:
				if (!isDataLoaded1 || !isDataLoaded2)
				{
					std::cout << "Unesite podatke atleta i eventova prvo!";
					break;
				}
				begin = std::chrono::high_resolution_clock::now();
				vector = events->getCitiesThatHostedOlympicsAtLeastOnce();
				for_each(vector.begin(), vector.end(), [](const std::string& x) {std::cout << x << std::endl; });
				end = std::chrono::high_resolution_clock::now();
				std::cout << "\nIzvrsena komanda za = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "." << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << std::endl;
				break;

			case 12:
				if (!isDataLoaded1 || !isDataLoaded2)
				{
					std::cout << "Unesite podatke atleta i eventova prvo!";
					break;
				}
				begin = std::chrono::high_resolution_clock::now();
				vectorTimova = events->getTeamsForGivenCountryAndGames(countries, games);
				for_each(vectorTimova.begin(), vectorTimova.end(), [](const Team& x) {std::cout << x << std::endl; });
				end = std::chrono::high_resolution_clock::now();
				std::cout << "\nIzvrsena komanda za = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "." << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << std::endl;
				break;

			case 13:
				if (!isDataLoaded1 || !isDataLoaded2)
				{
					std::cout << "Unesite podatke atleta i eventova prvo!";
					break;
				}
				begin = std::chrono::high_resolution_clock::now();
				vectorAthleta = events->getAllTheAthletesThatCompetedInPairOfGames(athletes, games);
				for_each(vectorAthleta.begin(), vectorAthleta.end(), [](const Athlete& x) {std::cout << x << std::endl; });
				end = std::chrono::high_resolution_clock::now();
				std::cout << "\nIzvrsena komanda za = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "." << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << std::endl;
				break;

			case 14:
				if (!isDataLoaded1 || !isDataLoaded2)
				{
					std::cout << "Unesite podatke atleta i eventova prvo!";
					break;
				}
				begin = std::chrono::high_resolution_clock::now();
				parovi = events->getPairOfCountryAthleteThatWonAtLeastOneMedalInTeamAndIndividual(athletes);
				for_each(parovi.begin(), parovi.end(), [](const std::pair<std::string, Athlete>& x) {std::cout << x.first << " - " << x.second << std::endl; });
				end = std::chrono::high_resolution_clock::now();
				std::cout << "\nIzvrsena komanda za = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "." << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << std::endl;
				break;

			default:
				std::cout << "Odabrana opcija ne postoji, izaberite ponovo.";
				break;
			}
		}
	}
	catch (std::exception e)
	{
		std::cout << "Error :: " << e.what() << std::endl;
	}
}