#include "Plane.h"
#include "Quad.h"

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
void initGL();
//void createTexture();
void render();
int close();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput();

GLFWwindow* window = NULL;
Quad quad;
Quad light;

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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
}

void initGL() {
	light.generateObj();
	quad.generateObj();
	light.loadTextureFromDisk("fire.png", false);
	quad.loadTextureFromDisk("wood.png", true);
}

void render() {

	float timeValue = glfwGetTime() / 2;
	float xOffset = sin(timeValue) / 1.2;
	float yOffset = cos(timeValue) / 1.2;

	quad.render(SCR_WIDTH, SCR_HEIGHT, glm::vec3(xOffset,yOffset, .0f), 0.5f, 50.f*timeValue, glm::vec3(1.f, 0.f, 0.f));
	light.render(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.f, 0.f, .0f), 0.5f, 50.f, glm::vec3(0.f, 1.f, 0.f));
	
}

int main() {

	createWindow();

	Shader ourShader("Organize.vert", "Texture.frag");
	Shader lightShader("Organize.vert", "Color.frag");

	initGL();


	glEnable(GL_DEPTH_TEST);

	light.setShader(&lightShader);
	quad.setShader(&ourShader);

	while (!glfwWindowShouldClose(window)) {

		processInput();
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	close();
}

int close() {
	light.clearGPU();
	quad.clearGPU();

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}