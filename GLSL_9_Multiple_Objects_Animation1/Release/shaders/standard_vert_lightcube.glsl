#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 3) in vec3 color;

out vec3 color3f;


uniform mat4 MVP;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	color3f = color;

	//gl_Position = projection * view * model * vec4(vertex, 1.0f);
	gl_Position = MVP*vec4(vertex,1.0f);
}
