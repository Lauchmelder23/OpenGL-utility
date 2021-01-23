#include <iostream>

#include "openglu.hpp"
#include "transformable.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

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
	// Setup GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const GLFWvidmode* screen = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int windowSize = screen->height / 4 * 3;

	// Create Window
	GLFWwindow* window = glfwCreateWindow(windowSize, windowSize, "Debug", NULL, NULL);
	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad stuff
	oglu::LoadGLLoader((GLADloadproc)glfwGetProcAddress);
	oglu::SetViewport(0, 0, windowSize, windowSize);

	// Create vertices for square
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,	// bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = { 
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	oglu::VertexAttribute topology[] = {
		{ 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0 },
		{ 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)) }
	};

	// Make a square
	oglu::Object square(vertices, sizeof(vertices), indices, sizeof(indices), topology, sizeof(topology));
	oglu::Object square2(square);

	square.Move(-0.6f, 0.0f, 0.0f);
	square2.Move(0.6f, 0.0f, 0.0f);

	//square.GlobalRotate(45.0f, 0.0f, 0.0f);
	//square.GlobalRotate(0.0f, 0.0f, 45.0f);

	//square.SetGlobalRotation(45.0f, 0.0f, 45.0f);

	// Create a shader
	oglu::Shader shader;
	try
	{
		shader = oglu::MakeShader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}

	// Create a texture
	oglu::Texture crate = oglu::MakeTexture("assets/crate.jpg");
	oglu::Texture opengl = oglu::MakeTexture("assets/opengl.png");

	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

	glm::mat4 projection(1.0f);
	projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);

	// Window loop
	oglu::Enable(GL_DEPTH_TEST);
	float t = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		oglu::ClearScreen(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, oglu::Color(0.29f, 0.13f, 0.23f));

		// view = glm::rotate(view, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		square.Pitch(6.0f);
		square2.Pitch(-6.0f);

		shader->Use();
		shader->SetUniform("texture1", crate, 0);
		shader->SetUniform("texture2", opengl, 1);
		shader->SetUniform("model", square);
		shader->SetUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(view));
		shader->SetUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projection));

		square.Render();

		shader->SetUniform("model", square2);
		square2.Render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		t += 0.1f;
	}

	glfwTerminate();
	return 0;
}
