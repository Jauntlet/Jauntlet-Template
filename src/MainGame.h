#pragma once
#include <Jauntlet/Jauntlet.h>
#include <Jauntlet/Time.h>
#include <Jauntlet/Rendering/Window.h>
#include <Jauntlet/Rendering/GLSLProgram.h>
#include <Jauntlet/Rendering/Textures/ResourceManager.h>
#include <Jauntlet/Rendering/Cameras/Camera.h>
#include <Jauntlet/Inputs/InputManager.h>
#include <Jauntlet/Rendering/Textures/SpriteBatch.h>

class MainGame {
public:
	MainGame();

	void run();

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();

	int _screenWidth = 1280, _screenHeight = 720;
	Window _window;

	GLSLProgram _colorProgram;
	
	Camera _camera;

	InputManager _inputManager;

	SpriteBatch _batch;

	float _fps = 0;
};