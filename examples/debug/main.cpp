#include <iostream>

#include "openglu.hpp"
#include "transformable.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,	// bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = { 
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	oglu::VertexAttribute topology[] = {
		{ 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0 },
		{ 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)) },
		{ 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)) }
	};

	// Make a square
	oglu::VertexArray square = oglu::MakeVertexArray(vertices, sizeof(vertices), indices, sizeof(indices), topology, sizeof(topology));

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

	oglu::Transformable model;
	//model.SetRotation(-55.0f, 0.0f, 0.0f);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.f), 1.0f, 0.1f, 100.0f);

	glm::mat4 test = glm::make_mat4(model.GetMatrix());

	// Window loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		oglu::ClearScreen(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, oglu::Color(0.29f, 0.13f, 0.23f));

		model.Rotate(6.0f, 0.0f, 0.0f);

		shader->Use();
		shader->SetUniform("texture1", crate, 0);
		shader->SetUniform("texture2", opengl, 1);
		shader->SetUniformMatrix4fv("model", 1, GL_FALSE, model.GetMatrix());
		shader->SetUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(view));
		shader->SetUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projection));

		square->BindAndDraw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
