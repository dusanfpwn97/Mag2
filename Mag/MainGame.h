#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include <vector>


enum class GameState { PLAY, EXIT };
class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();



private:

	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	void CalculateFPS();

	SDL_Window* _window;

	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	std::vector<Sprite*> _sprites;
	GLSLProgram _colorProgram;

	float _fps;
	float _frameTime;
	float _time;
	float _maxFPS;

};

