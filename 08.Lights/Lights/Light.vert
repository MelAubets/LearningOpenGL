#version 330 core
layout (location = 0) in vec3 aPos;

uniform float size;
uniform vec3 offset;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	gl_Position = projection * view * model * vec4(aPos*size+offset, 1.0);
}