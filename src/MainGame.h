#pragma once
#include <Jauntlet/Jauntlet.h>
#include <Jauntlet/Time.h>
#include <Jauntlet/Rendering/Window.h>
#include <Jauntlet/Rendering/GLSLProgram.h>
#include <Jauntlet/Rendering/Textures/ResourceManager.h>
#include <Jauntlet/Rendering/Cameras/Camera2D.h>
#include <Jauntlet/Inputs/InputManager.h>

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
	Jauntlet::Window _window;

	Jauntlet::GLSLProgram _colorProgram;
	
	Jauntlet::Camera2D _camera;

	Jauntlet::InputManager _inputManager;

	float _fps = 0;
};