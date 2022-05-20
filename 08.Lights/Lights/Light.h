#ifndef LIGHT_H
#define LIGHT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <shader/Shader.h>

class Light {
public:
	Light() {
		VAO = -1;
		VBO = -1;
		texture = -1;

		vertices.clear();

		shaderForDraw = nullptr;
	}

	void generateObj() {

		float vertices[] = {
			//Position			  //Color			 
			-0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  1.0f,

			-0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  1.0f,

			-0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  1.0f,

			-0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  1.0f
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void render(glm::vec3 position, glm::vec3 size, float zoom, float SCR_WIDTH, float SCR_HEIGHT, glm::mat4 view) {

		//Perspective
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.f);
		model = glm::translate(model, position);
		model = glm::scale(model, size);
		projection = glm::perspective(glm::radians(zoom), SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.f);

		//Set uniforms
		(*shaderForDraw).use();
		(*shaderForDraw).setMat4("model", model);
		(*shaderForDraw).setMat4("view", view);
		(*shaderForDraw).setMat4("projection", projection);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void clearGPU() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void setShader(Shader* shader) {
		shaderForDraw = shader;
	}

protected:
	unsigned int VAO, VBO, texture;
	std::vector<float> vertices;

	Shader* shaderForDraw;
};
#endif