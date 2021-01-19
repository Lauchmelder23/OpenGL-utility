#include <iostream>

#include "openglu.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	oglu::SetViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(int argc, char** argv)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const GLFWvidmode* screen = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int windowSize = screen->height / 4 * 3;

	GLFWwindow* window = glfwCreateWindow(windowSize, windowSize, "Debug", NULL, NULL);
	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	oglu::LoadGLLoader((GLADloadproc)glfwGetProcAddress);
	oglu::SetViewport(0, 0, windowSize, windowSize);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	oglu::VertexAttribute topology[] = {
		{ 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 }
	};

	oglu::Object triangle(vertices, sizeof(vertices), nullptr, 0, topology, sizeof(topology));
	
	oglu::Shader shader("shaders/vertexShader.vert", "");


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		oglu::ClearScreen(GL_COLOR_BUFFER_BIT, oglu::Color(0.29f, 0.13f, 0.23f));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
