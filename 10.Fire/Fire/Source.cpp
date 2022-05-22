#include "Plane.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"

#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader/Shader.h>

#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int createWindow();
void initGL(Shader shader);
void render(Shader shader);
int close();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput();

GLFWwindow* window = NULL;


Camera camera(glm::vec3(.0f, .0f, 3.f));
float lastX = SCR_WIDTH / 2.f;
float lastY = SCR_HEIGHT / 2.f;
bool firstMouse = true;

float deltaTime = 0.f;
float lastFrame = 0.f;

int i = 1;

Plane cube;

int createWindow() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Title", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;

		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
}

void initGL(Shader shader) {

	glEnable(GL_DEPTH_TEST);

	cube.setShader(&shader);

	cube.generateObj();

	cube.setTextures("flame5.png");

	shader.use();
	shader.setInt("cubeTexture", 0);
	//shader.setInt("material.dudv", 1);

}

void render(Shader shader) {
//
//	int i = 1;
//
//	float timeValue = glfwGetTime();
//
//	if (timeValue < .1) i = 1;
//	else if (timeValue < .2) i = 2;
//	else if (timeValue < .3) i = 3;
//	else if (timeValue < .4) i = 4;
//	else if (timeValue < .5) i = 5;
//	else if (timeValue < .6) i = 6;
//	else if (timeValue < .7) i = 7;
//	else if (timeValue < .8) i = 8;
//	else if (timeValue < .9) i = 9;
//	else if (timeValue < .10) i = 10;
//	else if (timeValue < .11) i = 11;
//	else if (timeValue < .12) i = 12;
//	else if (timeValue < .13) i = 13;
//	else if (timeValue < .14) i = 14;
//	else if (timeValue < .15) i = 15;
//	else if (timeValue < .16) { i = 16; }
//	else { glfwSetTime(0.0); }

//	std::string index = std::to_string(i);

	//cube.setTextures("flame5.png");

	shader.use();
	glm::vec3 position(.0f, .0f, .0f);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	shader.setVec3("light.duvduv", 0.5f, 1.0f, 0.5f);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	


	cube.render(position, glm::vec3(.5f));
}

int main() {

	createWindow();

	Shader shader("vertex.vert", "texture.frag");

	initGL(shader);

	while (!glfwWindowShouldClose(window)) {



		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glEnable(GL_DEPTH_TEST);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput();

		render(shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	close();
}

int close() {
	cube.clearGPU();

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}



