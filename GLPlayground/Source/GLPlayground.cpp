﻿// GLPlayground.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Renderer/GLRenderer.h"
#include "Renderer/ShaderProgram.h"
#include "Renderer/Mesh.h"
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <strstream>
#include "Logger/Logger.h"
#include "Managers/ResourceManager.h"
#include "Renderer/Texture.h"
#include "Renderer/GLUtilities.h"
#include "Renderer/RenderableScene.h"
#include "GameObjects/Scene.h"
#include "Managers/InputManager.h"


GLFWwindow * CreateWindow(const WindowInfo & Window, const std::string & WindowTitle)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

#ifdef GL_DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	return glfwCreateWindow(Window.Width, Window.Height, WindowTitle.c_str(), nullptr, nullptr);

}

int main()
{
	Logger::GetLogger().LogOnFile(true);

	GLRenderer renderer;
	InputManager & InputManagerInstance = InputManager::GetInputManager();

	if (glfwInit() == GL_FALSE)
	{
		return -1;
	}


	WindowInfo windowInfo{ 1300, 900 };
	GLFWwindow * window = CreateWindow(windowInfo, "OpenGL Renderer - Filtering");

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!renderer.Initialize(window))
	{
		glfwTerminate();
		return -1;
	}

	InputManagerInstance.Initialize(*window);
	RenderableScene renderScene(renderer);
	Scene scene(renderScene);

	renderScene.Initialize();
	scene.Init();
	

	double StartTime, EndTime;
	float DeltaTime = 0;

	while (!glfwWindowShouldClose(window))
	{
		StartTime = glfwGetTime();
		
		glfwPollEvents();

		

		scene.Update(DeltaTime);
		renderScene.RenderScene(DeltaTime);
<<<<<<< Updated upstream

		//std::stringstream stream;
		//stream << DeltaTime << std::ends;

		//Logger::GetLogger().LogString(stream.str(), LogType::LOG);
=======
	
		/*std::stringstream stream;
		stream << DeltaTime << std::ends;

		Logger::GetLogger().LogString(stream.str(), LogType::LOG);*/
>>>>>>> Stashed changes

		EndTime = glfwGetTime();

		DeltaTime = static_cast<float>(EndTime - StartTime);

	}

	scene.DeInit();
	renderScene.DeInitialize();
	

	glfwTerminate();

    return 0;
}

