#include "MainGame.h"
#include <iostream>
#include <string>
#include <EFE/errors.h>
#include <EFE/ResourceManager.h>

//#include "ImageLoader.h"


MainGame::MainGame() :
	_screenWidth(1024),			  
	_screenHeight(768),			   
	_gameState(GameState::PLAY),
	_time(0.f),			  
	_maxFPS(120.f)
	
{
	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{

}

void MainGame::run()
{
	initSystems();

	gameLoop();
}

void MainGame::initSystems()
{

	_window.create("Engine", _screenWidth, _screenHeight, 0);
	initShaders();
	_spriteBatch.init();
	_fpsLimiter.init(_maxFPS);
}

void MainGame::initShaders()
{
	_colorProgram.compileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		_fpsLimiter.beginFrame();


		_time += 0.06f;

		_camera.update();

		processInput();
		drawGame();

		_fps = _fpsLimiter.end();


		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 30)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
		
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	const float CAMERA_SPEED = 2.f;
	const float SCALE_SPEED = 0.02f;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			//case SDL_MOUSEMOTION:
				//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			case SDL_KEYDOWN:
				_inputManager.pressKey(evnt.key.keysym.sym);
				break;
			case SDL_KEYUP:
				_inputManager.releaseKey(evnt.key.keysym.sym);
				break;
		}
	}

	if (_inputManager.isKeyPressed(SDLK_w))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.f, CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_s))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.f, -CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_d))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.f));
	}
	if (_inputManager.isKeyPressed(SDLK_a))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.f));
	}
	if (_inputManager.isKeyPressed(SDLK_q))
	{
		_camera.setScale(_camera.getScale() + -SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDLK_e))
	{
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	}

}

void MainGame::drawGame()
{
	
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);

	//GLint timeLocation = _colorProgram.getUniformLocation("time");
	//glUniform1f(timeLocation, _time);

	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();

	glm::vec4 pos(0, 0, 11, 11);
	glm::vec4 uv(0, 0, 1, 1);
	static efe::GLTexture texture = efe::ResourceManager::getTexture("textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	efe::Color color;
	color.r = 255;
	color.b = 255;
	color.a = 255;

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			_spriteBatch.draw(pos, uv, texture.id, color, 0);
			_spriteBatch.draw(pos + glm::vec4(i * 11, j*11, 0, 0), uv, texture.id, color, 0);
		}
	}
	

	_spriteBatch.end();

	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unUse();

	_window.swapBuffer();
}
