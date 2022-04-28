#version 330 core
out vec4 FragColor;

uniform float ourColor;

void main(){
	FragColor = vec4(ourColor, .0f, .721f, .8f);
}
