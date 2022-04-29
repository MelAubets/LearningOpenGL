#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 posTransform;
uniform mat4 colTransform;
out vec4 ourColor;

void main(){
	gl_Position = posTransform * vec4(aPos, 1.0);
	ourColor = colTransform * vec4(aColor, 1.0);
}