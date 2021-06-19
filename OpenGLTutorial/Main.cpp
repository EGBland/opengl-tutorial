#include <iostream>
#include <iomanip>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "shader.h"

// init
void init();

// for glad framebuffer size callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// process function for main loop
void processInput(GLFWwindow* window);

// render function for main loop
void render(GLFWwindow* window);

// some data
const float vertices[] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 80.0f/255.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 32.0f/255.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 176.0f/255.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 128.0f/255.0f, 1.0f, 1.0f
};

const unsigned int indices[] = {
	0, 1, 2,
	1, 2, 3
};

int main() {
	// init
	init();

	// make a window
	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Window", NULL, NULL);
	if (window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// initialise glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialise GLAD" << std::endl;
		return -1;
	}

	// make a viewport
	glViewport(0, 0, 800, 600);

	// give glad another frame buffer size callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// make vao
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// make vbo
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// make ebo
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// load texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int tWidth, tHeight, tnChannels;
	unsigned char* tData = stbi_load("textures/texture.jpg", &tWidth, &tHeight, &tnChannels, 0);
	if (tData) {
		std::cout << "This image has " << tnChannels << " channels" << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, tData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(tData);

	// compile shaders
	Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

	// main loop
	int framecount = 0;
	while (!glfwWindowShouldClose(window)) {
		// process
		processInput(window);

		// render
		render(window);
		shader.use();
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		// glfw
		glfwSwapBuffers(window);
		glfwPollEvents();
		framecount++;
	}

	float theTime = glfwGetTime();
	std::cout << "Rendered " << framecount << " frames in " << std::setw(2) << theTime << " seconds (" << framecount / theTime << " fps)" << std::endl;
	// the end
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glfwTerminate();
	return 0;
}

void init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	stbi_set_flip_vertically_on_load(true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void render(GLFWwindow* window) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}