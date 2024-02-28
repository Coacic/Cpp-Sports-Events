#ifndef _GATHLETEDOESNOTEXIST_
#include <iostream>

class GAthleteDoesNotExist : std::exception {
public:
	GAthleteDoesNotExist() {
		std::cout << "Error : Atleta ne postoji\n";
	}
};

#endif //_GATHLETEDOESNOTEXIST_
