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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Title", NULL, NULL);
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

	Shader ourShader("shader.vert", "shader.frag");

	float vertices[] = {
		//Position        //Color
		 .05f, -.05f, .0f, 1.f, 0.101f, 0.666f,
		-.05f, -.05f, .0f, 1.f, 0.101f, 0.666f,
		 .00f,  .05f, .0f, 1.f, 0.101f, 0.666f
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		//Rendering commands here
		glClearColor(.176f, .035f, .227f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = glfwGetTime()/2;

		ourShader.use();

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i <10;i++) {
			glm::mat4 posTransform = glm::mat4(1.f);
			posTransform = glm::translate(posTransform, glm::vec3((sin(timeValue) / 1.2)*i/10, (cos((timeValue * 3.14)) / 1.2)*i/10, .0f));
			
			glm::mat4 colTransform = glm::mat4(1.f);
			colTransform = glm::translate(colTransform, glm::vec3((sin(timeValue) * i / 10), ((sin(timeValue) / 2 + 0.5f) * i / 10), ((sin(timeValue) / 2 + 0.5f) * i / 10)));
			
			ourShader.setMat4("posTransform", posTransform);
			ourShader.setMat4("colTransform", colTransform);

			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1,&VBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


}