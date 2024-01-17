#include "MainGame.h"

#include <iostream>
#include <Jauntlet/JMath.h>

MainGame::MainGame() 
	: 
	_window("Jauntlet Game Engine", _screenWidth, _screenHeight, 0),
	_camera(_screenWidth, _screenHeight) 
{
	// Empty
}

void MainGame::run() {
	initSystems();
	gameLoop();
}

void MainGame::initSystems() {
	// initialize Jauntlet
	Jauntlet::init();

	_camera.setPosition(glm::vec3(0, 0, 50));

	// set some default window properties
	_window.setBackgroundColor(Color(76, 24, 32));
	_window.setWindowIcon("Textures/Icon.png");
	
	// set default missing Texture
	Jauntlet::ResourceManager::setMissingTexture("Textures/Icon.png");
	
	// initialize shaders
	initShaders();
}

void MainGame::initShaders() {
	// compile a vertex and fragment shader, with properties to be able to render simple objects.
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop() {
	// set the max fps the game can run at. -1 uncaps framerate.
	Jauntlet::Time::setMaxFPS(60);

	while (true) {
		// start a frame
		Jauntlet::Time::beginFrame();
		
		// process user inputs
		processInput();
		
		// runs if the user quits the game through alt+f4, the X in the corner of the window, or any other means
		if (_inputManager.quitGameCalled()) {
			break;
		}

		// update the camera
		_camera.update();

		// draw the game
		drawGame();

		// end a frame. This returns the FPS of the game
		_fps = Jauntlet::Time::endFrame();
	}
}

void MainGame::processInput() {
	// processes all inputs by the user
	_inputManager.processInput();

	if (_inputManager.isKeyDown(SDLK_w)) {
		_camera.translate(glm::vec3(0.0f, 0.0f, -1.0f * Jauntlet::Time::getDeltaTime() * 10));
	}
	if (_inputManager.isKeyDown(SDLK_s)) {
		_camera.translate(glm::vec3(0.0f, 0.0f, 1.0f * Jauntlet::Time::getDeltaTime() * 10));
	}
	if (_inputManager.isKeyDown(SDLK_a)) {
		_camera.translate(glm::vec3(-1.0f * Jauntlet::Time::getDeltaTime() * 10, 0.0f, 0.0f));
	}
	if (_inputManager.isKeyDown(SDLK_d)) {
		_camera.translate(glm::vec3(1.0f * Jauntlet::Time::getDeltaTime() * 10, 0.0f, 0.0f));
	}
	if (_inputManager.isKeyDown(SDLK_q)) {
		_camera.translate(glm::vec3(0.0f, 1.0f * Jauntlet::Time::getDeltaTime() * 10, 0.0f));
	}
	if (_inputManager.isKeyDown(SDLK_e)) {
		_camera.translate(glm::vec3(0.0f, -1.0f * Jauntlet::Time::getDeltaTime() * 10, 0.0f));
	}

	if (_inputManager.isKeyDown(SDLK_LEFT)) {
		_camera.rotateX(-0.4f * Jauntlet::Time::getDeltaTime());
	}
	if (_inputManager.isKeyDown(SDLK_RIGHT)) {
		_camera.rotateX(0.4f * Jauntlet::Time::getDeltaTime());
	}
	if (_inputManager.isKeyDown(SDLK_UP)) {
		_camera.rotateY(-0.4f * Jauntlet::Time::getDeltaTime());
	}
	if (_inputManager.isKeyDown(SDLK_DOWN)) {
		_camera.rotateY(0.4f * Jauntlet::Time::getDeltaTime());
	}
}

void MainGame::drawGame() {
	// Reset screen
	_window.clearScreen();
	
	// activate shaders
	_colorProgram.use();
	
	// activate camera
	_camera.setActive();

	_batch.begin();
	_batch.draw(glm::vec4(-16, -16, 32, 32), Jauntlet::ResourceManager::getTexture("Textures/craig.png").id);
	_batch.endAndRender();

	// disable shaders
	_colorProgram.unuse();
	
	// put the newly rendered objects on screen
	_window.swapBuffer();
}