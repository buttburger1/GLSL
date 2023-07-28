#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec4 testColor;

out vec4 outColor;

uniform mat4 shapemodel;
uniform mat4 shapeview;
uniform mat4 shapeprojection;

uniform mat4 shapeMVP;

void main()
{
	gl_Position = shapeMVP*vec4(vertex,1.0f);
	outColor = testColor;
}

