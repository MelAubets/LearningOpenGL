#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float xOffset;
uniform float yOffset;
uniform float colOffset;
out vec3 ourColor;

void main(){
	gl_Position = vec4(aPos.x+xOffset, aPos.y + yOffset, aPos.z, 1.0);
	ourColor = vec3(aColor.x+colOffset, aColor.y, aColor.z);
}