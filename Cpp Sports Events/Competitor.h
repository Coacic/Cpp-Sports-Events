#ifndef _COMPETITOR_H_
#define _COMPETITOR_H_
#include <iostream>
#include <regex>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <chrono>
#include <thread>
#include <mutex>
#include <thread>
#include <future>
#include <utility>
#include <memory>
#include "GAthleteDoesNotExist.h"
#include "GTeamDoesNotExist.h"
#include "Countries.h"
#include "Sports.h"
#include "Games.h"

class Competitor {
	virtual void parseCompetitor() = 0;
};

#endif // !_COMPETITOR_H_