#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;
//layout(location = 3) in vec3 vertexColor;



out vec2 UV;
out vec3 Normal;
out vec3 FragPos;


uniform mat4 MVP;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 mat4Rot;


void main()
{
	FragPos = vec3(model * vec4(vertex,1.0f));
	//FragPos = vec3(MVP * vec4(vertex,1.0f));



	Normal = vertexNormal;
	//Normal = vertexNormal * mat3(mat4Rot);
	//Normal = mat3(transpose(inverse(model))) * vertexNormal;
	UV = vertexUV;



	//gl_Position = projection * view * model * vec4(vertex, 1.0f);
	gl_Position = MVP*vec4(vertex,1.0f);
}
