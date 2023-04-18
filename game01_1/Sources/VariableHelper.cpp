#include "../Headers/VariableHelper.h"

namespace variables
{
	std::string playername;
	std::string playerscore;

	void setPlayerName(std::string newname)
	{
		playername = newname;
	}

	std::string* getPlayerName()
	{
		return &playername;
	}

	void setPlayerScore(std::string newscore)
	{
		playerscore = newscore;
	}

	std::string* getPlayerScore()
	{
		return &playerscore;
	}
}