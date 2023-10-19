#version 330 core

layout(location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 fontMVP;

void main()
{
	gl_Position = fontMVP * vec4(vertex.xy, 0.0f, 1.0f);
	TexCoords = vertex.zw;
}
