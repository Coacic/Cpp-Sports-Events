#ifndef _MEDALS_H_
#define _MEDALS_H_
#include "Events.h"
class Medal {
	std::vector<std::pair<Event*, int>> medalsEvents;
	std::vector<std::pair<Athlete*, int>> medalsAthletes;
public:
	Medal();
};
#endif // !_MEDALS_H_