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
	camera.aspectRatio = ((float)width / (float)height);
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
		camera.SetPosition(camera.GetPosition() + 0.1f * glm::normalize(glm::vec3(camera.GetFront().x, 0.0f, camera.GetFront().z)));

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.Sideways(-0.1f);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.SetPosition(camera.GetPosition() - 0.1f * glm::normalize(glm::vec3(camera.GetFront().x, 0.0f, camera.GetFront().z)));

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
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Model loading test", NULL, NULL);
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

	camera.Move(0.0f, 0.0f, 5.0f);

	// Window loop
	oglu::Enable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	oglu::Color bgColor = oglu::Color::Black;

	oglu::Model model("assets/backpack.obj");

	oglu::SpotLight flashlight;
	flashlight.linear = 0.022f;
	flashlight.quadratic = 0.0019f;
	flashlight.angle = 18.0f;
	flashlight.outerAngle = 24.9f;

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		oglu::ClearScreen(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, bgColor);

		flashlight.SetPosition(camera.GetPosition());
		flashlight.direction = camera.GetFront();

		shader->Use();

		shader->SetUniformMatrix3fv("normal", 1, GL_FALSE, glm::value_ptr(model.GetNormalMatrix()));
		shader->SetUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model.GetMatrix()));
		shader->SetUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(camera.GetMatrix()));
		shader->SetUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(camera.GetProjection()));

		shader->SetUniform3fv("flashlight.position", 1, flashlight.GetPositionPointer());
		shader->SetUniform3fv("flashlight.direction", 1, glm::value_ptr(flashlight.direction));
		shader->SetUniform("flashlight.angle", glm::cos(glm::radians(flashlight.angle)));
		shader->SetUniform("flashlight.outerAngle", glm::cos(glm::radians(flashlight.outerAngle)));
		shader->SetUniform("flashlight.constant", flashlight.constant);
		shader->SetUniform("flashlight.linear", flashlight.linear);
		shader->SetUniform("flashlight.quadratic", flashlight.quadratic);

		model.Render(shader);
		
		model.Rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;
}
