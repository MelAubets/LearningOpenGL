#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColorCoord;
layout (location = 2) in vec2 aTexCoord;

uniform float size;
uniform vec3 offset;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 colorCoord;
out vec2 texCoord;

void main(){
	gl_Position = projection * view * model * vec4(aPos*size+offset, 1.0);
	texCoord = vec2(aTexCoord.x, aTexCoord.y);
	colorCoord = aColorCoord;
}