#include "MainGame.h"
#include <iostream>
#include <string>
#include <EFE/errors.h>
#include <EFE/ResourceManager.h>

// Konstruktor: Inicijalizacija privatnih varijabli koristeći inicijaliznu listu
MainGame::MainGame() :
	_screenWidth(1920),			  
	_screenHeight(1080),			   
	_gameState(GameState::PLAY),		  
	_maxFPS(75.f),
	_fps(0.0f)
	
{
	_camera.init(_screenWidth, _screenHeight);
}

// U dekonstruktoru trenutno ne radimo ništa
MainGame::~MainGame()
{

}

// Polazna tačka programa
void MainGame::run()
{
	// Inicijalizacija potrebnih sistema
	initSystems();
	// Pokretanje glavne petlje za simulaciju
	gameLoop();
}

// Inicijalizacija OpenGL šejder programa
void MainGame::initSystems()
{
	// Kreiranje prozora, sa imenom, širinom i visinom i dodatnim opcijama za tip prozora
	_window.create("Zavrsni rad - Dusan Fajler", _screenWidth, _screenHeight, 0);
	// Inicijalizacija OpenGL šejder programa
	initShaders();
	// Inicijalizacija _spriteBatch instance koju ćemo da koristimo za grupno iscrtavanje boida
	_spriteBatch.init();
	// Inicijalizacija _fpsLimiter instance koju koristimo za limitiranje koliko ćemo frejmova
	// u sekundi obrađivati
	_fpsLimiter.init(_maxFPS);
	// Postavljanje granica u kojima će se stvoriti boidi
	_boidManager.updateBounds(_screenWidth, _screenHeight);
	// Stvaranje boida 
	_boidManager.spawnBoids(300, glm::vec2(0.f, 0.f));

}

// Inicijalizacija OpenGL šejder programa
void MainGame::initShaders()
{
	// Kompajliranje OpenGL šejdera iz putanje
	_colorProgram.compileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
	// Dodavanje atributa _colorProgram instanci koju ćemo da koristimo za iscrtavanje boida
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	// Linkovanje šejdera
	_colorProgram.linkShaders();
}

void MainGame::gameLoop()
{
	// Dok stanje igre nije EXIT, obrađivati igru
	while (_gameState != GameState::EXIT)
	{
		// Signaliziranje _fpsLimiter-u da je frejm počeo
		_fpsLimiter.beginFrame();
		// Provera da li je dobijen neki ulaz iz miša ili tastature
		processInput();
		// Računanje simulacije za sledeći frejm
		_boidManager.updateBoids();
		// Ažuriranje kamere
		_camera.update();
		// iscrtavanje simulacije
		drawGame();
		// Signaliziranje _fpsLimiter-u da se frejm završio
		_fps = _fpsLimiter.end();
	}
}

// Provera da li je dobijen neki ulaz iz miša ili tastature
void MainGame::processInput()
{
	// SDL struct događaja koji ćemo da napunimo uskoro
	SDL_Event evnt;
	
	// Setovanje brzine kretanja kamere i brzine skaliranja
	const float CAMERA_SPEED = 10.f;
	const float SCALE_SPEED = 0.02f;

	// Punjenje evnt varijable i prolazak kroz petlju za sve inpute
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			// Ako je kliknut X u gornjem desnom uglu prozora menjamo stanje igre u EXIT i u sledećem frejmu izlazimo iz igre
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			// Signaliziranje našem input manageru da je stisnuto dugme i prosleđivanje koje je dugme stisnuto
			case SDL_KEYDOWN:
				_inputManager.pressKey(evnt.key.keysym.sym);
				break;
				// Signaliziranje našem input manageru da je pušteno dugme i prosleđivanje koje je dugme pušteno
			case SDL_KEYUP:
				_inputManager.releaseKey(evnt.key.keysym.sym);
				break;
				// Signaliziranje našem input manageru da je stisnut klik i prosleđivanje koji je klik stisnut
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.pressKey(evnt.button.button);
				break;
				// Signaliziranje našem input manageru da je pušten klik i prosleđivanje koji je klik pušten
			case SDL_MOUSEBUTTONUP:
				_inputManager.releaseKey(evnt.button.button);
				break;
				// Signaliziranje našem input manageru da je miš pomeren na neko novo mesto i prosleđivanje koorinata
			case SDL_MOUSEMOTION:
				_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
				break;
		}
	}

	// Pomeranje kamere Gore, Dole, Levo, Desno, ako su stisnuti WSAD dugmici, respektivno
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
	// Zumiranje kamere ako je stisnuto Q ili E dugme
	if (_inputManager.isKeyPressed(SDLK_q))
	{
		_camera.setScale(_camera.getScale() + -SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDLK_e))
	{
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	}
	// Stvaranje boida ako je stisnut levi klik
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		// Uzimamo koorinate miša iz našeg input managera
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		// Konvertujemo koordinate miša na prozoru u koordinate u svetu
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		// Stvaramo boide
		_boidManager.spawnBoids(1, mouseCoords);
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

	_boidManager.drawBoids(_spriteBatch);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unUse();

	_window.swapBuffer();
}


