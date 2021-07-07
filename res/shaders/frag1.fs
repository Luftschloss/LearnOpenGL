#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
in vec2 TexCoord;

uniform float ourAlpha;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	vec4 finalColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), ourAlpha);
	FragColor = vec4(vertexColor, 0.0) * finalColor;
}