#version 330 core

struct Material {
	vec3 ambient;

	//vec3 diffuse;
	sampler2D diffuse;

	//vec3 specular;
	sampler2D specular;

	sampler2D emission;

	float shininess;
};

uniform Material material;

uniform sampler2D myTexture;


struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;




out vec4 FragColor;

in vec2 UV;
in vec3 Normal;

//in vec3 outColor;
in vec3 FragPos;



uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec4 testColor;

uniform vec3 viewPos;

uniform float time;


void main()
{
	//FragColor = texture(myTexture, UV).rgba;//* outColor;
	//FragColor = texture(myTexture, UV).rgba;// * testColor;
	//FragColor = texture(myTexture, UV).rgba * testColor;
	//FragColor = testColor;
	//FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//FragColor = vec4(lightColor * objectColor, 1.0f);


	//float ambientStrength = 0.1f;
	//vec3 ambient = ambientStrength * lightColor;
	//vec3 result = ambient * objectColor;
	//FragColor = vec4(result, 1.0f);


	//vec3 norm = normalize(Normal);
	//vec3 lightDir = normalize(lightPos - FragPos);

	//float diff = max(dot(norm, lightDir), 0.0f);
	//vec3 diffuse = diff * lightColor;

	//vec3 result = (ambient + diffuse) * objectColor;
	//FragColor = vec4(result, 1.0f);




	//float specularStrength = 0.5f;
	//vec3 viewDir = normalize(viewPos - FragPos);

	//vec3 reflectDir = reflect(-lightDir, norm);
	//float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	//vec3 specular = specularStrength * spec * lightColor;

	//vec3 result = (ambient + diffuse + specular) * objectColor;
	//FragColor = vec4(result, 1.0f);



	// ambient
	//vec3 ambient = lightColor * material.ambient;
	//vec3 ambient  = light.ambient * material.ambient;

	// diffuse
	vec3 norm = normalize(Normal);

	vec3 lightDir = normalize(lightPos - FragPos);
	//vec3 lightDir = normalize(lightPos);

	float diff = max(dot(norm, lightDir), 0.0f);
	//vec3 diffuse = lightColor * (diff * material.diffuse);
	//vec3 diffuse  = light.diffuse * (diff * material.diffuse);


	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	//vec3 viewDir = normalize(viewPos);


	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	//vec3 specular = lightColor * (spec * material.specular);
	//vec3 specular = light.specular * (spec * material.specular);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));


	vec3 emission = vec3(0.0);
	if (texture(material.specular, UV).r == 0.0)
	{
		emission = texture(material.emission, UV).rgb;
		emission = texture(material.emission, UV + vec2(0.0,time)).rgb;
		emission = emission * (sin(time) * 0.5 + 0.5) * 2.0;
	}



	//vec3 result = ambient + diffuse + specular;

	vec4 result = vec4(ambient + diffuse + specular + emission, 1.0f);
	FragColor = result;

	//FragColor = vec4(result, 1.0f);
	//FragColor = vec4(1.0f);
}
