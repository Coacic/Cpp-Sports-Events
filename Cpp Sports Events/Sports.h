#ifndef _SPORTS_H_
#define	_SPORTS_H_
#include <iostream>
#include <vector>

class Sports {
	std::vector<std::string> sports;

public:
	Sports();
	Sports(int i);
	~Sports();
	std::string* getSport(int i);
	std::string* findSport(std::string);
	void pushSport(std::string);
	friend std::ostream& operator<<(std::ostream& os, const Sports& s);
};

#endif // !_SPORTS_H_
