#ifndef _COUNTRIES_H_
#define _COUNTRIES_H_
#include <iostream>
#include <vector>

class Countries {
	std::vector<std::string> countries;

public:
	Countries();
	Countries(int i);
	~Countries();
	std::string* findCountry(std::string);
	void pushCountry(std::string);
};

#endif // !_COUNTRIES_H_