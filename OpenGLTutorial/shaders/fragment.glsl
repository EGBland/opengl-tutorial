#version 330 core
in vec2 theTexCoord;
in vec3 theColor;
out vec4 FragColor;
uniform sampler2D ourTexture;
void main() {
	FragColor = texture(ourTexture, theTexCoord);
}