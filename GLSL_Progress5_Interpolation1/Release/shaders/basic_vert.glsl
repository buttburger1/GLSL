#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec3 vertexColor;

out vec2 UV;
out vec3 outColor;


uniform mat4 MVP;

void main()
{
	gl_Position = MVP*vec4(vertex,1.0f);
	UV = vertexUV;
	outColor = vertexColor;
}