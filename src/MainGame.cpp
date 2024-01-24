#include "MainGame.h"
#include <cmath>

MainGame::MainGame() 
	: 
	_window("Jauntlet Game Engine", _screenWidth, _screenHeight, 0),
	_camera(_screenWidth, _screenHeight) 
{
	glGenFramebuffers(1, &gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

	glGenTextures(1, &gPosition);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, _screenWidth, _screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

	glGenTextures(1, &gNormal);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, _screenWidth, _screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

	glGenTextures(1, &gColorSpec);
	glBindTexture(GL_TEXTURE_2D, gColorSpec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _screenWidth, _screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gColorSpec, 0);

	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);
}

void MainGame::run() {
	initSystems();
	gameLoop();
}

void MainGame::initSystems() {
	// initialize Jauntlet
	Jauntlet::init();

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
	_colorProgram.compileShaders("Shaders/model.vert", "Shaders/model.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
	
	_lightingProgram.compileShaders("Shaders/gbuffer.vert", "Shaders/gbuffer.frag");
	_lightingProgram.addAttribute("texCoords");
	_lightingProgram.addAttribute("fragPos");
	_lightingProgram.addAttribute("normal");
	_lightingProgram.linkShaders();
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

		// end a frame. This can be made to return the FPS of the game.
		Jauntlet::Time::endFrame();
	}
}

void MainGame::processInput() {
	// processes all inputs by the user
	_inputManager.processInput();

	if (_inputManager.isKeyDown(SDLK_w)) {
		_camera.translate(glm::vec3(-8.0f * cos(_cameraRotationX + M_PI_2) * Jauntlet::Time::getDeltaTime(), 0.0f, -8.0f * sin(_cameraRotationX + M_PI_2) * Jauntlet::Time::getDeltaTime()));
	}
	if (_inputManager.isKeyDown(SDLK_s)) {
		_camera.translate(glm::vec3(8.0f * cos(_cameraRotationX + M_PI_2) * Jauntlet::Time::getDeltaTime(), 0.0f, 8.0f * sin(_cameraRotationX + M_PI_2) * Jauntlet::Time::getDeltaTime()));
	}
	if (_inputManager.isKeyDown(SDLK_a)) {
		_camera.translate(glm::vec3(-8.0f * cos(_cameraRotationX) * Jauntlet::Time::getDeltaTime(), 0.0f, -8.0f * sin(_cameraRotationX) * Jauntlet::Time::getDeltaTime()));
	}
	if (_inputManager.isKeyDown(SDLK_d)) {
		_camera.translate(glm::vec3(8.0f * cos(_cameraRotationX) * Jauntlet::Time::getDeltaTime(), 0.0f, 8.0f * sin(_cameraRotationX) * Jauntlet::Time::getDeltaTime()));
	}
	if (_inputManager.isKeyDown(SDLK_q)) {
		_camera.translate(glm::vec3(0.0f, 4.0f * Jauntlet::Time::getDeltaTime(), 0.0f));
	}
	if (_inputManager.isKeyDown(SDLK_e)) {
		_camera.translate(glm::vec3(0.0f, -4.0f * Jauntlet::Time::getDeltaTime(), 0.0f));
	}
	
	if (_inputManager.isKeyDown(SDLK_LEFT)) {
		_camera.rotateX(-0.8f * Jauntlet::Time::getDeltaTime());
		_cameraRotationX -= 0.8f * Jauntlet::Time::getDeltaTime();
	}
	if (_inputManager.isKeyDown(SDLK_RIGHT)) {
		_camera.rotateX(0.8f * Jauntlet::Time::getDeltaTime());
		_cameraRotationX += 0.8f * Jauntlet::Time::getDeltaTime();
	}
	if (_inputManager.isKeyDown(SDLK_UP)) {
		_camera.rotateY(-0.8f * Jauntlet::Time::getDeltaTime());
	}
	if (_inputManager.isKeyDown(SDLK_DOWN)) {
		_camera.rotateY(0.8f * Jauntlet::Time::getDeltaTime());
	}
}

void MainGame::drawGame() {
	// Reset screen
	_window.clearScreen();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gColorSpec);

	_lightingProgram.use();

	glUniform1i(_lightingProgram.getUniformLocation("texture_diffuse"), gPosition);
	glUniform1i(_lightingProgram.getUniformLocation("texture_specular"), gColorSpec);

	// activate shaders
	_colorProgram.use();
	
	// activate camera
	_camera.setActive();
	
	monkey.draw();

	// disable shaders
	_colorProgram.unuse();
	
	// put the newly rendered objects on screen
	_window.swapBuffer();
}