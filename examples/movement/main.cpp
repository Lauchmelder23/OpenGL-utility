#include <iostream>
#include <vector>

#include "openglu.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();

	// Create vertices for square
	float vertices[] = {
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f
	};

	oglu::VertexAttribute topology[] = {
		{ 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0 },
		{ 1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)) },
		{ 2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)) }
	};

	// Make a square
	oglu::VertexArray cubeDefault = oglu::MakeVertexArray(vertices, sizeof(vertices), nullptr, 0, topology, sizeof(topology));
	oglu::SharedMaterial cubeMaterial(new oglu::Material);

	//cubeMaterial->AddProperty("ambient", oglu::Color::White);
	cubeMaterial->AddProperty("shininess", 32.f);
	cubeMaterial->AddProperty("diffuse", oglu::MakeTexture("assets/tiles_diffuse.jpg"));
	cubeMaterial->AddProperty("specular", oglu::MakeTexture("assets/tiles_bump.jpg"));

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

	for (oglu::Object& cube : cubes)
		cube.material = cubeMaterial;

	oglu::Object lightSource(cubeDefault);
	lightSource.SetScale(glm::vec3(0.1f));

	oglu::PointLight pointLight;
	pointLight.LinkPositionToTransformable(lightSource);

	oglu::SpotLight flashlight;
	flashlight.linear = 0.09f;
	flashlight.quadratic = 0.032f;

	// Create a shader
	oglu::Shader shader, lightSourceShader;
	try
	{
		shader = oglu::MakeShader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
		lightSourceShader = oglu::MakeShader("shaders/lightSourceShader.vert", "shaders/lightSourceShader.frag");
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}

	oglu::AmbientLight ambient;
	ambient.intensity = 0.1f;

	camera.Move(0.0f, 0.0f, 5.0f);

	// Window loop
	oglu::Enable(GL_DEPTH_TEST);
	float t = 0.0f;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	oglu::Color bgColor = oglu::Color::Black;
	lightSource.SetPosition(1.0f, 1.0f, -1.0f);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		oglu::ClearScreen(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, bgColor);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		flashlight.SetPosition(camera.GetPosition());
		flashlight.direction = camera.GetFront();

		shader->Use();

		shader->SetUniform("pointLight.ambient", "pointLight.ambientStrength", ambient);
		shader->SetUniform3fv("pointLight.position", 1, glm::value_ptr(lightSource.GetPosition()));
		shader->SetUniform("pointLight.diffuse", pointLight.diffusionColor, true);
		shader->SetUniform("pointLight.specular", pointLight.specularColor, true);
		shader->SetUniform("pointLight.constant", pointLight.constant);
		shader->SetUniform("pointLight.linear", pointLight.linear);
		shader->SetUniform("pointLight.quadratic", pointLight.quadratic);

		shader->SetUniform3fv("fl.position", 1, glm::value_ptr(camera.GetPosition()));
		shader->SetUniform3fv("fl.direction", 1, glm::value_ptr(flashlight.direction));
		shader->SetUniform("fl.angle", glm::cos(glm::radians(flashlight.angle)));
		shader->SetUniform("fl.outerAngle", glm::cos(glm::radians(flashlight.outerAngle)));
		shader->SetUniform("fl.diffuse", flashlight.diffusionColor, true);
		shader->SetUniform("fl.specular", flashlight.specularColor, true);
		shader->SetUniform("fl.constant", flashlight.constant);
		shader->SetUniform("fl.linear", flashlight.linear);
		shader->SetUniform("fl.quadratic", flashlight.quadratic);

		shader->SetUniform3fv("viewPos", 1, glm::value_ptr(camera.GetPosition()));

		shader->SetUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(camera.GetMatrix()));
		shader->SetUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(camera.GetProjection()));

		shader->SetUniformTexture("material.diffuse", cubeMaterial->GetPropertyValue<oglu::Texture>("diffuse"), 0);
		shader->SetUniformTexture("material.specular", cubeMaterial->GetPropertyValue<oglu::Texture>("specular"), 1);
		shader->SetUniform("material.shininess", cubeMaterial->GetPropertyValue<float>("shininess"));

		for (oglu::Object& cube : cubes)
		{
			shader->SetUniform("model", cube);
			shader->SetUniformMatrix3fv("normal", 1, GL_FALSE, glm::value_ptr(cube.GetNormalMatrix()));

			cube.Render();
		}

		lightSourceShader->Use();
		lightSourceShader->SetUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(lightSource.GetMatrix(true)));
		lightSourceShader->SetUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(camera.GetMatrix()));
		lightSourceShader->SetUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(camera.GetProjection()));
		lightSourceShader->SetUniform("color", pointLight.diffusionColor, true);
		lightSource.Render();

		ImGui::Begin("Controls");

		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if(ImGui::CollapsingHeader("Scene"));
		{
			ImGui::ColorEdit3("Background color", &bgColor.r);
			ImGui::SliderFloat("FOV", &camera.fov, 30.0f, 100.0f);
			ImGui::SliderFloat("zNear", &camera.zNear, 0.01, 1.0f);
			ImGui::SliderFloat("zFar", &camera.zFar, 2.0f, 100.0f);
		}

		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if(ImGui::CollapsingHeader("Lighting"))
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);
			if (ImGui::TreeNode("Ambient"))
			{
				ImGui::ColorEdit3("Color", &ambient.color.r);
				ImGui::SliderFloat("Intensity", &ambient.intensity, 0.0f, 1.0f);

				ImGui::TreePop();
				ImGui::Separator();
			}

			ImGui::SetNextItemOpen(true, ImGuiCond_Once);
			if (ImGui::TreeNode("Point"))
			{
				ImGui::ColorEdit3("Diffusion", &pointLight.diffusionColor.r);
				ImGui::ColorEdit3("Specular", &pointLight.specularColor.r);
				ImGui::SliderFloat3("Position", pointLight.GetPositionPointer(), -5.0f, 5.0f);

				ImGui::SetNextItemOpen(true, ImGuiCond_Once);
				if (ImGui::TreeNode("Attenuation"))
				{
					ImGui::SliderFloat("Constant", &pointLight.constant, 1.0f, 4.0f);
					ImGui::SliderFloat("Linear", &pointLight.linear, 0.0014f, 0.7f);
					ImGui::SliderFloat("Quadratic", &pointLight.quadratic, 0.00007f, 1.8f);

					ImGui::TreePop();
				}

				ImGui::TreePop();
			}

			ImGui::SetNextItemOpen(true, ImGuiCond_Once);
			if (ImGui::TreeNode("Flashlight"))
			{
				ImGui::ColorEdit3("Diffusion", &flashlight.diffusionColor.r);
				ImGui::ColorEdit3("Specular", &flashlight.specularColor.r);
				ImGui::SliderFloat("Angle", &flashlight.angle, 1.0f, flashlight.outerAngle - 1.0f);
				ImGui::SliderFloat("Outer angle", &flashlight.outerAngle, flashlight.angle + 1.0f, 60.0f);

				ImGui::SetNextItemOpen(true, ImGuiCond_Once);
				if (ImGui::TreeNode("Attenuation"))
				{
					ImGui::SliderFloat("Constant", &flashlight.constant, 1.0f, 4.0f);
					ImGui::SliderFloat("Linear", &flashlight.linear, 0.0014f, 0.7f);
					ImGui::SliderFloat("Quadratic", &flashlight.quadratic, 0.00007f, 1.8f);

					ImGui::TreePop();
				}

				ImGui::TreePop();
			}
		}

		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::CollapsingHeader("Cube Material"))
		{
			ImGui::SliderFloat("Shininess", cubeMaterial->GetProperty<float>("shininess"), 1.0f, 256.0f);
		}

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();

		t += 0.05f;
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}