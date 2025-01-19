#version 330 core

struct Material {
	vec3 ambient;
	sampler2D diffuse;//vec3 diffuse;
	sampler2D normal;
	sampler2D specular;//vec3 specular;
	sampler2D emission;
	float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NUM_DIR_LIGHTS 10
uniform int numDirLights;

//uniform DirLight dirLight[4];
uniform DirLight dirLight[NUM_DIR_LIGHTS];
//uniform DirLight dirLight;

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NUM_POINT_LIGHTS 30
uniform int numPointLights;

//uniform PointLight pointLight[4];
uniform PointLight pointLight[NUM_POINT_LIGHTS];
//uniform PointLight pointLight;


struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
#define NUM_SPOT_LIGHTS 10
uniform int numSpotLights;

//uniform SpotLight spotLight;
uniform SpotLight spotLight[NUM_SPOT_LIGHTS];


uniform int shiftColor;

uniform int shaderFlow;
uniform int shaderEmission;
uniform float time;
uniform vec3 viewPos;
//uniform vec3 lightPos;//TEST
//uniform vec3 lightColor;//TEST
//uniform vec3 objectColor;//TEST
//uniform vec4 testColor;//TEST


uniform sampler2D myTexture;
//uniform Light light;
//uniform DirLight dirLight;
//uniform PointLight pointLight;
//uniform SpotLight spotLight;
uniform Material material;


uniform sampler2D DiffuseTextureSampler;
uniform sampler2D NormalTextureSampler;
uniform sampler2D SpecularTextureSampler;


in vec3 Position_worldspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

in vec3 LightDirection_tangentspace;
in vec3 EyeDirection_tangentspace;



in vec2 UV;
in vec3 Normal;
//in vec3 outColor;
in vec3 FragPos;
in vec3 vColor;

//out vec3 FragColor;
out vec4 FragColor;


// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


//vec3 lightDir = normalize(lightPos);
//vec3 lightDir = normalize(lightPos - FragPos);//BASIC1
//vec3 lightDir = normalize(light.position - FragPos);//BASIC2
//vec3 lightDir = normalize(-light.direction);//SUN_TEST
//vec3 lightDir = normalize(light.position - FragPos);//POINT_LIGHT//SPOT_LIGHT

uniform mat3 MV3x3;
uniform vec3 lightPos;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);


	//vec3 ambient = dirLight.ambient * vec3(texture(material.diffuse, UV));
	//vec3 diffuse = dirLight.diffuse * vec3(texture(material.diffuse, UV));
	//vec3 specular = dirLight.specular * vec3(texture(material.specular, UV));

	//vec3 ambient = vec3(0.1,0.1,0.1) * dirLight.ambient;
	//vec3 diffuse = texture(material.diffuse, UV).rgb;
	//vec3 specular = texture(material.specular, UV).rgb * 0.3;



	vec3 result;
	//vec3 result = CalcDirLight(dirLight, norm, viewDir);
	//result += CalcPointLight(pointLight, norm, FragPos, //viewDir);
	//result += CalcSpotLight(spotLight, norm, FragPos, //viewDir);

	for(int i = 0; i < numPointLights; i++)
	{
		//if(i == 0 && numDirLights == 0)
		if(i == 0)//NOT INCREMENTING THE FIRST RESULT
		{
			result = CalcPointLight(pointLight[i], norm, FragPos, viewDir);
		}
		else
		{
			result += CalcPointLight(pointLight[i], norm, FragPos, viewDir);
		}
	}

	for(int i = 0; i < numDirLights; i++)
	{
		if(i == 0 && numPointLights == 0)
		{
			result = CalcDirLight(dirLight[i], norm, viewDir);
		}
		else
		{
			result += CalcDirLight(dirLight[i], norm, viewDir);
		}
	}

	//for(int i = 0; i <= 0; i++)
	for(int i = 0; i <= numSpotLights; i++)
	{
		if(i == 0 && numPointLights == 0 && numDirLights == 0)
		{
			result = CalcSpotLight(spotLight[i], norm, FragPos, viewDir);
		}
		else
		{
			result += CalcSpotLight(spotLight[i], norm, FragPos, viewDir);
		}
	}

	//if(shiftColor == 0)
	//{
		//FragColor = vec4(result, 1.0f);
	//}
	//else if(shiftColor == 1)
	//{
		//FragColor = vec4(vColor, 1.0f);
	//}

	FragColor = vec4(result, 1.0f);
	//FragColor = vec4(1.0f);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	//NORMAL MAP
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 40.0;

	vec3 TextureNormal_tangentspace = normalize(texture( NormalTextureSampler, vec2(UV.x,UV.y) ).rgb*2.0 - 1.0);
	//vec3 TextureNormal_tangentspace = normalize(texture( material.normal, vec2(UV.x,UV.y) ).rgb*2.0 - 1.0);

	float distance = length( light.direction - Position_worldspace );

	vec3 n = TextureNormal_tangentspace;
	vec3 l = normalize(LightDirection_tangentspace);
	float cosTheta = clamp( dot( n,l ), 0,1 );

	vec3 E = normalize(EyeDirection_tangentspace);
	vec3 R = reflect(-l,n);
	float cosAlpha = clamp( dot( E,R ), 0,1 );

	//DIRLIGHT
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));
	//vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));
	//vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	if(shiftColor == 0)
	{
		ambient = light.ambient * vec3(texture(material.diffuse, UV));
		diffuse = (light.diffuse * diff * vec3(texture(material.diffuse, UV)) * LightColor * LightPower * cosTheta / (distance*distance));
		specular = (light.specular * spec * vec3(texture(material.specular, UV)) * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance));
	}
	if(shiftColor == 1)
	{
		ambient = light.ambient * vColor;
		diffuse = light.diffuse * diff * vColor;
		specular = light.specular * spec * vColor;
	}

	//EMISSION
	vec3 emission = vec3(0.0);
	if (texture(material.specular, UV).r == 0.0)
	{
		emission = texture(material.emission, UV).rgb;
		emission = texture(material.emission, UV + vec2(0.0,time)).rgb;
		emission = emission * (sin(time) * 0.5 + 0.5) * 2.0;
	}

	if(shaderEmission == 0)
	{
		return (ambient + diffuse + specular);
	}
	else if(shaderEmission == 1)
	{
		//return (ambient + diffuse + specular + emission);
		return (ambient + diffuse + specular + emission);
	}
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	//NORMAL MAP
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 40.0;

	vec3 TextureNormal_tangentspace = normalize(texture( NormalTextureSampler, vec2(UV.x,UV.y) ).rgb*2.0 - 1.0);
	//vec3 TextureNormal_tangentspace = normalize(texture( material.normal, vec2(UV.x,UV.y) ).rgb*2.0 - 1.0);

	float distance = length( light.position - Position_worldspace );

	vec3 n = TextureNormal_tangentspace;
	vec3 l = normalize(LightDirection_tangentspace);
	float cosTheta = clamp( dot( n,l ), 0,1 );

	vec3 E = normalize(EyeDirection_tangentspace);
	vec3 R = reflect(-l,n);
	float cosAlpha = clamp( dot( E,R ), 0,1 );


	//POINTLIGHT
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	float distance2 = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance2 + light.quadratic * (distance2 * distance2));

	//vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));
	//vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));
	//vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	if(shiftColor == 0)
	{
		ambient = light.ambient * vec3(texture(material.diffuse, UV));
		diffuse = (light.diffuse * diff * vec3(texture(material.diffuse, UV)) * LightColor * LightPower * cosTheta / (distance*distance));
		specular = (light.specular * spec * vec3(texture(material.specular, UV)) * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance));
	}
	if(shiftColor == 1)
	{
		ambient = light.ambient * vColor;
		diffuse = (light.diffuse * diff * vColor * LightColor * LightPower * cosTheta / (distance*distance));
		specular = (light.specular * spec * vColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance));
	}

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	//EMISSION
	vec3 emission = vec3(0.0);
	if (texture(material.specular, UV).r == 0.0)
	{
		emission = texture(material.emission, UV).rgb;
		emission = texture(material.emission, UV + vec2(0.0,time)).rgb;
		emission = emission * (sin(time) * 0.5 + 0.5) * 2.0;
	}


	if(shaderEmission == 0)
	{
		return (ambient + diffuse + specular);
	}
	else if(shaderEmission == 1)
	{
		//return (ambient + diffuse + specular + emission);
		return (ambient + diffuse + specular + emission);
	}
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	//NORMAL MAP
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 40.0;

	vec3 TextureNormal_tangentspace = normalize(texture( NormalTextureSampler, vec2(UV.x,UV.y) ).rgb*2.0 - 1.0);
	//vec3 TextureNormal_tangentspace = normalize(texture( material.normal, vec2(UV.x,UV.y) ).rgb*2.0 - 1.0);

	float distance = length( light.position - Position_worldspace );

	vec3 n = TextureNormal_tangentspace;
	vec3 l = normalize(LightDirection_tangentspace);
	float cosTheta = clamp( dot( n,l ), 0,1 );

	vec3 E = normalize(EyeDirection_tangentspace);
	vec3 R = reflect(-l,n);
	float cosAlpha = clamp( dot( E,R ), 0,1 );

	//SPOTLIGHT
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	float distance2 = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance2 + light.quadratic * (distance2 * distance2));    
	float theta = dot(lightDir, normalize(-light.direction)); 
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	//vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));
	//vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));
	//vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	if(shiftColor == 0)
	{
		ambient = light.ambient * vec3(texture(material.diffuse, UV));
		diffuse = (light.diffuse * diff * vec3(texture(material.diffuse, UV)) * LightColor * LightPower * cosTheta / (distance*distance));
		specular = (light.specular * spec * vec3(texture(material.specular, UV)) * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance));
	}
	if(shiftColor == 1)
	{
		ambient = light.ambient * vColor;
		diffuse = (light.diffuse * diff * vColor * LightColor * LightPower * cosTheta / (distance*distance));
		specular = (light.specular * spec * vColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance));
	}

	//ambient *= attenuation * intensity;
	ambient *= intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	//EMISSION
	vec3 emission = vec3(0.0);
	if (texture(material.specular, UV).r == 0.0)
	{
		emission = texture(material.emission, UV).rgb;
		emission = texture(material.emission, UV + vec2(0.0,time)).rgb;
		emission = emission * (sin(time) * 0.5 + 0.5) * 2.0;
	}

	if(shaderEmission == 0)
	{
		return (ambient + diffuse + specular);
	}
	else if(shaderEmission == 1)
	{
		//return (ambient + diffuse + specular);
		return (ambient + diffuse + specular + emission);
	}
}
