#version 330 core

in vec4 outColor;

out vec4 FragColor;

uniform vec4 testColor;

void main()
{
	//float lin = 1.0/gl_FragCoord.w;
	//float depth = (lin - 0.5)/(16.0 - 0.5);

	//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	//FragColor = testColor;
	FragColor = vec4(outColor);
}

