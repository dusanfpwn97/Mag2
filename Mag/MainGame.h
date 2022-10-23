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

	efe::Window _window;
	efe::Camera2D _camera;

	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	efe::GLSLProgram _colorProgram;

	efe::SpriteBatch _spriteBatch;

	float _fps;
	float _frameTime;
	float _time;
	float _maxFPS;

};

