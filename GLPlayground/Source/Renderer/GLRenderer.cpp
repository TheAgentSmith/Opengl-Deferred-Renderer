#include "stdafx.h"
#include "GLRenderer.h"
#include <assert.h>
#include <sstream>
#include "Logger/Logger.h"

void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::stringstream logStream;

	logStream << message << std::ends;

	Logger::GetLogger().LogString(logStream.str(), LogType::LOG);
}

GLRenderer::GLRenderer()
{
}


bool GLRenderer::Initialize(GLFWwindow * Window)
{
	assert(Window);

	Context = Window;

	int width, height = 0;

	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	glDebugMessageCallback(&DebugCallback, this);

	GLint majorVersionNumber = 0;
	GLint minorVersionNumber = 0;

	glGetIntegerv(GL_MAJOR_VERSION, &majorVersionNumber);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersionNumber);

	std::stringstream versionLog;

	versionLog << "OpenGL version number is : " << majorVersionNumber << "." << minorVersionNumber << std::ends;

	Logger::GetLogger().LogString(versionLog.str(), LogType::LOG);

	glfwGetFramebufferSize(Context, &width, &height);
	glViewport(0, 0, width, height);

	//glPointSize(500.f);

	return true;

}

void GLRenderer::Clear()
{
	glClearColor(ClearColor.x, ClearColor.y, ClearColor.z, ClearColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRenderer::Present()
{
	glfwSwapBuffers(Context);
}

void GLRenderer::DrawMesh(Mesh & mesh)
{
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh.GetIndices().size(), GL_UNSIGNED_INT, 0);
}

void GLRenderer::EnableDepthTest(bool Enable)
{
	DepthTestEnabled = Enable;
	Enable ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

GLRenderer::~GLRenderer()
{
}

void GLRenderer::SetClearColor(const glm::vec4 & Color)
{
	ClearColor = Color;
}
