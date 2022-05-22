#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D screenTexture;

void main(){
	vec4 col = texture(screenTexture, texCoord).rgba;
	FragColor = col;
}
