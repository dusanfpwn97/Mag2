#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <EFE/EFE.h>
#include <EFE/Sprite.h>
#include <EFE/GLSLProgram.h>
#include <EFE/GLTexture.h>
#include <EFE/Window.h>
#include <EFE/Camera2D.h>
#include <EFE/SpriteBatch.h>
#include <EFE/InputManager.h>
#include <EFE/Timing.h>
#include <vector>

#include "Boid.h"
#include "BoidManager.h"



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

	efe::Window _window;
	efe::Camera2D _camera;

	int _screenWidth;
	int _screenHeight;
	GameState _gameState;
	BoidManager _boidManager;

	efe::GLSLProgram _colorProgram;
	efe::InputManager _inputManager;
	efe::SpriteBatch _spriteBatch;
	efe::FpsLimiter _fpsLimiter;


	float _maxFPS;
	float _fps;
	float _time;

};

