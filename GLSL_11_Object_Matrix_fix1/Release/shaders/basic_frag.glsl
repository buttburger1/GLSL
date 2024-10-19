#version 330 core

in vec2 UV;
in vec3 outColor;

out vec4 FragColor;

uniform sampler2D myTexture;

uniform vec4 testColor;

void main()
{
	//FragColor = texture(myTexture, UV).rgba;//* outColor;
	FragColor = texture(myTexture, UV).rgba; //* testColor;
	//FragColor = vec4(outColor, 1.0f);
}