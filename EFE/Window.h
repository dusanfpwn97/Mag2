#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>

namespace efe
{
	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };


	class Window
	{
	public:
		Window();
		~Window();


		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		void swapBuffer();

		int getScreenWidgth() { return _screenWidth; }
		int getScreeenHeight() { return _screenHeight; }
	private:
		SDL_Window* _sdlWindow;

		int _screenWidth;
		int _screenHeight;
	};

}