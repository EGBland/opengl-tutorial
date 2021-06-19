#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec3 theColor;
out vec2 theTexCoord;
void main() {
	gl_Position = vec4(aPos, 1.0);
	theColor = aColor;
	theTexCoord = aTexCoord;
}