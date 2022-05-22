#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D cubeTexture;
uniform sampler2D dudvTexture;

void main(){
	vec4 ambient = texture(cubeTexture, texCoord);
	vec4 dudv =  texture(dudvTexture, texCoord);

	FragColor = ambient+dudv;
}
