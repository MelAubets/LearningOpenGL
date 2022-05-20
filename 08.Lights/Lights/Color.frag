#version 330 core
out vec4 FragColor;

in vec3 fragPos;
in vec2 texCoord;
in vec3 normal;

uniform vec3 lightPos;
uniform vec3 camPos;
uniform vec3 objectColor;


void main(){
	
	float ambientStrenght = 0.1;
	vec3 ambient = ambientStrenght * vec3(1.0);

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1.0);

	float specularStrenght = 0.5f;
	vec3 viewDir = normalize(camPos-fragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
	vec3 specular = specularStrenght * spec * vec3(1.0);

	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0);
}
