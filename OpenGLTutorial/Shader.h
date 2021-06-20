#pragma once

class Shader {
protected:
	unsigned int program;
public:
	Shader(const char* vPath, const char* fPath);
	unsigned int getProgram();
	void use();
};