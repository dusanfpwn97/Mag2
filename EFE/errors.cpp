#include "errors.h"
#include <iostream>
#include <cstdlib>
#include <SDL/SDL.h>
namespace efe
{
	void fatalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		int tmp;
		std::cin >> tmp;
		SDL_Quit();
		exit(1);
	}

}