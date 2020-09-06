#version 330 core
out vec4 FragColor;

uniform vec4 objectColor;
uniform vec4 lightColor;

void main()
{
	float ambientStrength = 0.2;
	vec4 ambient = ambientStrength * lightColor;

	FragColor = ambient * objectColor;
}