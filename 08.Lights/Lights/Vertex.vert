#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColorCoord;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

uniform float size;
uniform vec3 offset;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPos;
out vec3 colorCoord;
out vec2 texCoord;
out vec3 normal;

void main(){
	fragPos = vec3(model*vec4(aPos*size+offset, 1.0));

	texCoord = vec2(aTexCoord.x, aTexCoord.y);
	colorCoord = aColorCoord;
	normal = aNormal;

	gl_Position = projection * view * vec4(fragPos, 1.0);
}