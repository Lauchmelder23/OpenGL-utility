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
	GLFWwindow* window = glfwCreateWindow(windowSize, windowSize, "Utah teapot", NULL, NULL);
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

	oglu::VertexArray utah_model;
	try {
		utah_model = oglu::MakeVertexArray("assets/utah.obj");
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}

	oglu::Object utah(utah_model);

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

	oglu::Enable(GL_DEPTH_TEST);

	oglu::Camera camera(45.0f, 1.0f, 0.1f, 100.0f);
	camera.Move(0.0f, -5.0f, -10.0f);
	camera.LookAt(glm::value_ptr(glm::make_vec3(utah.GetPosition()) + glm::vec3(0.0f, 2.0f, 0.0f)));

	float t = 0.0f;

	// Window loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		oglu::ClearScreen(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, oglu::Color(0.29f, 0.13f, 0.23f));

		utah.Rotate(0.0f, 10.0f, 0.0f);

		shader->Use();
		shader->SetUniform("model", utah);
		shader->SetUniformMatrix4fv("view", 1, GL_FALSE, camera.GetMatrix());
		shader->SetUniformMatrix4fv("projection", 1, GL_FALSE, camera.GetProjectionMatrix());

		oglu::PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		utah.Render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		t += 0.01f;
	}

	glfwTerminate();
	return 0;
}
