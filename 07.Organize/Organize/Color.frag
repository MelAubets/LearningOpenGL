#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 colorCoord;

void main(){
	FragColor = vec4(colorCoord, 1.f);
}
