#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include "Shader.h"

Shader::Shader(const char* vPath, const char* fPath) {
	std::ifstream vin, fin;
	vin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::string vSrc, fSrc;
	try {
		std::stringstream vstr, fstr;

		vin.open(vPath);
		vstr << vin.rdbuf();
		vin.close();

		fin.open(fPath);
		fstr << fin.rdbuf();
		fin.close();

		vSrc = vstr.str();
		fSrc = fstr.str();
	}
	catch (std::ifstream::failure ex) {
		std::cout << ex.what() << std::endl;
	}

	const char* vSrcC = vSrc.c_str();
	const char* fSrcC = fSrc.c_str();

	unsigned int vertexShader, fragShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vSrcC, NULL);
	glCompileShader(vertexShader);
	// error check vertex shader
	int success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char log[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		std::cout << "Error compiling vertex shader: " << log << std::endl;
	}

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fSrcC, NULL);
	glCompileShader(fragShader);
	// error check frag shader
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char log[512];
		glGetShaderInfoLog(fragShader, 512, NULL, log);
		std::cout << "Error compiling fragment shader: " << log << std::endl;
	}
	
	this->program = glCreateProgram();
	glAttachShader(this->program, vertexShader);
	glAttachShader(this->program, fragShader);
	glLinkProgram(this->program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	glGetProgramiv(this->program, GL_LINK_STATUS, &success);
	if (!success) {
		char log[512];
		glGetProgramInfoLog(this->program, 512, NULL, log);
		std::cout << "Error linking program: " << log << std::endl;
	}
}

unsigned int Shader::getProgram() {
	return this->program;
}

void Shader::use() {
	glUseProgram(this->program);
}