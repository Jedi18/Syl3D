#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	FragColor = mix(texture(texture0, texCoord), texture(texture1, vec2(texCoord.x, texCoord.y)), 0.2f);
}