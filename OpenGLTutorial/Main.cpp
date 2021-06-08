#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// for glad framebuffer size callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// process function for main loop
void processInput(GLFWwindow* window);

// render function for main loop
void render(GLFWwindow* window);

int main() {
	// init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	// main loop
	while (!glfwWindowShouldClose(window)) {
		// process
		processInput(window);

		// render
		render(window);

		// glfw
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// the end
	glfwTerminate();
	return 0;
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