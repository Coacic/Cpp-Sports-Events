#ifndef _GTEAMDOESNOTEXIST_H_
#define _GTEAMDOESNOTEXIST_H_
#include <iostream>

class GTeamDoesNotExist : std::exception {
public:
	GTeamDoesNotExist() {
		std::cout << "Error : Tim ne postoji\n";
	}
};

#endif // !_GTEAMDOESNOTEXIST_H_
