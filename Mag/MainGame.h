#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <EFE/EFE.h>
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

	// Polazna tačka programa
	void run();

private:

	// Inicijalizacija potrebnih sistema
	void initSystems();
	// Inicijalizacija OpenGL šejder programa
	void initShaders();
	// Glavna petlja za simulaciju
	void gameLoop();
	// Primanje inputa
	void processInput();
	// iscrtavanje simulacije
	void drawGame();

	GameState _gameState;
	BoidManager _boidManager;

	efe::Window _window;
	efe::Camera2D _camera;
	efe::GLSLProgram _colorProgram;
	efe::InputManager _inputManager;
	efe::SpriteBatch _spriteBatch;
	efe::FpsLimiter _fpsLimiter;

	// Širina i visina prozora
	int _screenWidth;
	int _screenHeight;

	// Maksimalni broj frejmova u sekundi
	float _maxFPS;
	// Trenutni broj frejmova u sekundi
	float _fps;

};

