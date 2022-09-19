#include "MainGame.h"
#include <iostream>
#include <string>

void fatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	int tmp;
	std::cin >> tmp;
	SDL_QUIT;
}

MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 1280;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();

	_sprite.init(-1, -1, 1, 1);
	gameLoop();
}

void MainGame::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("EF Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr) fatalError("SDL Window could not be created!");
	
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);

	if (glContext == nullptr)
	{
		fatalError("SDL_GL context could not be created!");
	}

	GLenum error = glewInit();
	if(error != GLEW_OK) fatalError("Cloud not init GLEW");

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.f, 0.1f, 0.2f, 1.f);
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			//case SDL_MOUSEMOTION:
				//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
				

		}
	}
	
}

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	_sprite.draw();
	SDL_GL_SwapWindow(_window);
}
