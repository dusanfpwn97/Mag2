#include "EFE.h"
#include <SDL/SDL.h>
#include <GL/glew.h>


namespace efe
{
	void init()
	{

		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	}

}