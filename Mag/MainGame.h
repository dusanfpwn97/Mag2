#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <EFE/EFE.h>
#include <EFE/Sprite.h>
#include <EFE/GLSLProgram.h>
#include <EFE/GLTexture.h>
#include <vector>
#include <EFE/Window.h>


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

	efe::Window _window;

	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	std::vector<efe::Sprite*> _sprites;
	efe::GLSLProgram _colorProgram;

	float _fps;
	float _frameTime;
	float _time;
	float _maxFPS;

};

