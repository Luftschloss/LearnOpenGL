#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform float ourAlpha;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	vec4 finalColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), ourAlpha);
	FragColor = finalColor;
}