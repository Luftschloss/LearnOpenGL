#version 330 core

out vec3 fragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	fragColor = vec4(lightColor * objectColor, 1.0f);
}