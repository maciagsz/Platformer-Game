#define SFML_DEFINE_DISCRETE_GPU_PREFERENCE

import Headers;
#include "Headers/Game.h"

int main()
{
	try
	{
		GameInterface game; //start of the game
		game.Run();
	}
	catch (const std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

	return 0;
}