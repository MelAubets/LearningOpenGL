#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform float offset;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;

void main(){
	gl_Position = projection * view * model * vec4(aPos.x, aPos.y+offset, aPos.z, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}