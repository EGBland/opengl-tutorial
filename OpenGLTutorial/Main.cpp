#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
	-0.8f, -0.5f, 0.0f,
	-0.6f, -0.5f, 0.0f,
	-0.7f,  0.5f, 0.0f,
	 0.6f, -0.5f, 0.0f,
	 0.8f, -0.5f, 0.0f,
	 0.7f,  0.5f, 0.0f
};

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"\tgl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragShaderSource[] = { "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"\tFragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
"}\0",

"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"\t FragColor = vec4(1.0f,1.0f,0.0f,1.0f);\n"
"}\0"
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

	// make vaos
	unsigned int vao[2];
	glGenVertexArrays(2, vao);
	
	// make vbos
	unsigned int vbo[2];
	glGenBuffers(2, vbo);

	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices + 9, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// compile shaders
	unsigned int vertexShader;
	unsigned int fragShaders[2], shaderPrograms[2];
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	fragShaders[0] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShaders[0], 1, &fragShaderSource[0], NULL);
	glCompileShader(fragShaders[0]);
	fragShaders[1] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShaders[1], 1, &fragShaderSource[1], NULL);
	glCompileShader(fragShaders[1]);
	shaderPrograms[0] = glCreateProgram();
	glAttachShader(shaderPrograms[0], vertexShader);
	glAttachShader(shaderPrograms[0], fragShaders[0]);
	glLinkProgram(shaderPrograms[0]);
	shaderPrograms[1] = glCreateProgram();
	glAttachShader(shaderPrograms[1], vertexShader);
	glAttachShader(shaderPrograms[1], fragShaders[1]);
	glLinkProgram(shaderPrograms[1]);
	glDeleteShader(vertexShader);
	glDeleteShader(fragShaders[0]);
	glDeleteShader(fragShaders[1]);

	// main loop
	while (!glfwWindowShouldClose(window)) {
		// process
		processInput(window);

		// render
		render(window);
		glUseProgram(shaderPrograms[0]);
		glBindVertexArray(vao[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderPrograms[1]);
		glBindVertexArray(vao[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		

		// glfw
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// the end
	glfwTerminate();
	return 0;
}

void init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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