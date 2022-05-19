#version 330 core
out vec4 FragColor;

in vec3 fragPos;
in vec2 texCoord;
in vec3 colorCoord;
in vec3 normal;

uniform vec3 lightPos;
uniform vec3 objectColor;


void main(){
	
	float ambientStrenght = 0.1;
	vec3 ambient = ambientStrenght * vec3(1.f);

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1.f);

	vec3 result = (ambient + diffuse) * objectColor;
	FragColor = vec4(result, 1.0);
}
