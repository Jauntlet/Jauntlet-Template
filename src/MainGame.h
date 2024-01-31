#pragma once
#include <Jauntlet/Jauntlet.h>
#include <Jauntlet/Time.h>
#include <Jauntlet/Rendering/Window.h>
#include <Jauntlet/Rendering/GLSLProgram.h>
#include <Jauntlet/Rendering/Textures/ResourceManager.h>
#include <Jauntlet/Rendering/Cameras/Camera.h>
#include <Jauntlet/Inputs/InputManager.h>
#include <Jauntlet/Rendering/Textures/SpriteBatch.h>
#include <Jauntlet/Rendering/Model.h>
#include <Jauntlet/Scenes/Scene.h>

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

	float _cameraRotationX = 0.0f;

	InputManager _inputManager;

	Model monkey = Model(ModelType::OBJ, "Models/monkey.obj", "Textures/Icon.png");
	
	Scene scene = Scene("Logs/scene.json");
};