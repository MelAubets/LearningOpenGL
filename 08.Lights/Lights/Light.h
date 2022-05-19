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

	void render(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT, glm::vec3 offset, float size, float rotationAngle, glm::vec3 rotationAxis) {

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		//Perspective
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.f);
		glm::mat4 projection = glm::mat4(1.f);
		model = glm::rotate(model, glm::radians(rotationAngle), rotationAxis);
		view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));
		projection = glm::perspective(glm::radians(45.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.f);

		//Set uniforms
		(*shaderForDraw).use();
		(*shaderForDraw).setFloat("size", size);
		(*shaderForDraw).setVec3("offset", offset);
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