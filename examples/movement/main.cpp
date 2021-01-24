#include <iostream>
#include <vector>

#include "openglu.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

bool firstMouse = true;
bool escaped = false;
double lastX = 0.0f;
double lastY = 0.0f;

oglu::Camera camera(45.0f, 16.f / 9.f, 0.01f, 100.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	oglu::SetViewport(0, 0, width, height);
	camera.SetAspectRatio((float)width / (float)height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (escaped)
		return;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - (float)lastX;
	float yoffset = (float)lastY - (float)ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera.Pan(-xoffset);
	camera.Tilt(yoffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
	{
		escaped = !escaped;
		firstMouse = true;
		glfwSetInputMode(window, GLFW_CURSOR, escaped ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	}
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.Forward(0.1f);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.Sideways(-0.1f);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.Forward(-0.1f);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.Sideways(0.1f);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.Move(0.0f, 0.1f, 0.0f);

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.Move(0.0f, -0.1f, 0.0f);
}

int main(int argc, char** argv)
{
	// Setup GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const GLFWvidmode* screen = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int windowHeight = screen->height / 5 * 4;
	int windowWidth = (int)(16.f / 9.f * windowHeight);

	// Create Window
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "First Person Movement Test", NULL, NULL);
	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);

	// glad stuff
	oglu::LoadGLLoader((GLADloadproc)glfwGetProcAddress);
	oglu::SetViewport(0, 0, windowWidth, windowHeight);

	// Create vertices for square
	float vertices[] = {
		 0.5f,  0.5f, 0.5f,		1.0f, 1.0f, // front top right
		 0.5f, -0.5f, 0.5f,		1.0f, 0.0f,	// front bottom right
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, // front bottom left
		-0.5f,  0.5f, 0.5f,		0.0f, 1.0f, // front top left 

		 0.5f,  0.5f, -0.5f,	0.0f, 1.0f, // back top right
		 0.5f, -0.5f, -0.5f,	0.0f, 0.0f,	// back bottom right
		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, // back bottom left
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f  // back top left 
	};

	unsigned int indices[] = {
		0, 1, 3,	// front
		1, 2, 3,
		7, 4, 0,	// top
		7, 0, 3,
		0, 4, 5,	// right
		0, 5, 1,
		7, 3, 2,	// right
		7, 2, 6,
		2, 1, 6,	// bottom
		1, 6, 5,
		4, 7, 5,	// back
		7, 6, 5
	};

	oglu::VertexAttribute topology[] = {
		{ 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0 },
		{ 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)) }
	};

	// Make a square
	oglu::VertexArray cubeDefault = oglu::MakeVertexArray(vertices, sizeof(vertices), indices, sizeof(indices), topology, sizeof(topology));
	oglu::Object cubes[10] = { 
		oglu::Object(cubeDefault),
		oglu::Object(cubeDefault),
		oglu::Object(cubeDefault),
		oglu::Object(cubeDefault),
		oglu::Object(cubeDefault),
		oglu::Object(cubeDefault),
		oglu::Object(cubeDefault),
		oglu::Object(cubeDefault),
		oglu::Object(cubeDefault),
		oglu::Object(cubeDefault) 
	};

	cubes[0].SetPosition(0.0f, 0.0f, 0.0f);
	cubes[1].SetPosition(2.0f, 5.0f, -15.0f);
	cubes[2].SetPosition(-1.5f, -2.2f, -2.5f);
	cubes[3].SetPosition(-3.8f, -2.0f, -12.3f);
	cubes[4].SetPosition(2.4f, -0.4f, -3.5f);
	cubes[5].SetPosition(-1.7f, 3.0f, -7.5f);
	cubes[6].SetPosition(1.3f, -2.0f, -2.5f);
	cubes[7].SetPosition(1.5f, 2.0f, -2.5f);
	cubes[8].SetPosition(1.5f, 0.2f, -1.5f);
	cubes[9].SetPosition(-1.3f, 1.0f, -1.5f);

	cubes[0].SetRotation(45.0f, 30.0f, 1.0f);
	cubes[1].SetRotation(270.0f, 90.0f, 70.0f);
	cubes[2].SetRotation(-80.0f, -190.0f, 270.0f);
	cubes[3].SetRotation(100.0f, -200.0f, -120.3f);
	cubes[4].SetRotation(240.0f, -40.0f, -30.5f);
	cubes[5].SetRotation(-170.0f, 300.0f, -75.0f);
	cubes[6].SetRotation(130.0f, -20.0f, -250.0f);
	cubes[7].SetRotation(150.0f, 200.0f, -25.0f);
	cubes[8].SetRotation(150.0f, 20.0f, -150.0f);
	cubes[9].SetRotation(-130.0f, 10.0f, -150.0f);

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

	camera.Move(0.0f, 0.0f, 5.0f);

	// Window loop
	oglu::Enable(GL_DEPTH_TEST);
	float t = 0.0f;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		oglu::ClearScreen(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, oglu::Color(0.29f, 0.13f, 0.23f));

		shader->Use();
		shader->SetUniform("texture1", crate, 0);
		shader->SetUniform("texture2", opengl, 1);
		shader->SetUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(camera.GetMatrix()));
		shader->SetUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(camera.GetProjection()));

		for (oglu::Object& cube : cubes)
		{
			shader->SetUniform("model", cube);
			cube.Render();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

		t += 0.05f;
	}

	glfwTerminate();
	return 0;
}
