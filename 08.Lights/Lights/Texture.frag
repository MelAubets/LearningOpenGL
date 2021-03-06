#version 330 core
out vec4 FragColor;

in vec3 lightColor;
in vec2 texCoord;

uniform sampler2D texture;

void main(){
	FragColor = texture(texture, texCoord);
}
