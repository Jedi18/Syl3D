#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float visibility;

void main()
{
	FragColor = mix(texture(texture1, texCoord * 2), texture(texture2, vec2(texCoord.x * 2, texCoord.y * 2)), visibility);
}