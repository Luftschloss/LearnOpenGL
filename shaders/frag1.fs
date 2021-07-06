#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
uniform float ourAlpha;
void main()
{
	FragColor = vec4(vertexColor, 0.0) * ourAlpha;
}