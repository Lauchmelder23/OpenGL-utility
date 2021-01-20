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
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f // top left 
	};

	unsigned int indices[] = { 
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	oglu::VertexAttribute topology[] = {
		{ 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0 },
		{ 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)) }
	};
	
	oglu::Shader* shader;
	try 
	{
		shader = new oglu::Shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}

	oglu::Object square(vertices, sizeof(vertices), indices, sizeof(indices), topology, sizeof(topology));

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		oglu::ClearScreen(GL_COLOR_BUFFER_BIT, oglu::Color(0.29f, 0.13f, 0.23f));

		shader->SetUniform("ourColor", &oglu::Color::Transparent);
		shader->Use();
		square.BindAndDraw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
