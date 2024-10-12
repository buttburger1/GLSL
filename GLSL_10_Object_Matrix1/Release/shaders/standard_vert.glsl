#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec3 vertexColor;
layout(location = 4) in vec3 vertexTangent;
layout(location = 5) in vec3 vertexBitangent;


out vec2 UV;
out vec3 Normal;
out vec3 vColor;
out vec3 FragPos;


out vec3 Position_worldspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

out vec3 LightDirection_tangentspace;
out vec3 EyeDirection_tangentspace;


uniform mat4 MVP;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 mat4Rot;
uniform mat3 MV3x3;
uniform vec3 lightPos;


void main()
{
	vColor = vertexColor;

	FragPos = vec3(model * vec4(vertex,1.0f));
	//FragPos = vec3(MVP * vec4(vertex,1.0f));

	Normal = vertexNormal;
	//Normal = vertexNormal * mat3(mat4Rot);
	//Normal = mat3(transpose(inverse(model))) * vertexNormal;
	UV = vertexUV;

	//gl_Position = projection * view * model * vec4(vertex, 1.0f);
	gl_Position = MVP*vec4(vertex,1.0f);

	

	Position_worldspace = (model * vec4(vertex, 1)).xyz;
	//Position_worldspace = (MVP * vec4(vertex, 1)).xyz;
	vec3 vertexPosition_cameraspace = (view * model * vec4(vertex, 1)).xyz;
	EyeDirection_cameraspace = vec3(0 ,0 , 0) - vertexPosition_cameraspace;

	vec3 LightPosition_cameraspace = (view * vec4(lightPos, 1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;



	vec3 vertexTangent_cameraspace = mat3(view * model) * vertexTangent;//MV3x3
	vec3 vertexBitangent_cameraspace = mat3(view * model) * vertexBitangent;//MV3x3
	vec3 vertexNormal_cameraspace = mat3(view * model) * vertexNormal;//MV3x3

	mat3 TBN = transpose(mat3(
		vertexTangent_cameraspace,
		vertexBitangent_cameraspace,
		vertexNormal_cameraspace	
	)); // You can use dot products instead of building this matrix and transposing it. See References for details.

	LightDirection_tangentspace = TBN * LightDirection_cameraspace;
	EyeDirection_tangentspace =  TBN * EyeDirection_cameraspace;
}
