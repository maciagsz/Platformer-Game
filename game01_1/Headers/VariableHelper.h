#pragma once
#include <string>

namespace variables
{
	extern void setPlayerName(std::string);
	extern std::string* getPlayerName();

	extern void setPlayerScore(std::string);
	extern std::string* getPlayerScore();
}
