#version 330 core

in vec3 exFragmentPosition;
in vec3 exNormal;
in vec2 exTexcoord;

out vec4 FragmentColor;

uniform vec3 ViewPosition;

uniform sampler2D tex;

struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emissive;

    float shininess;
};  
uniform Material material;

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights [NR_POINT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);  

void main(void)
{
	// properties
    vec3 norm = normalize(exNormal);
    vec3 viewDir = normalize(ViewPosition - exFragmentPosition);

    // phase 1: Directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, exFragmentPosition, viewDir);    
    // phase 3: Spot light
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
    
    FragmentColor = vec4(result, 1.0);

	//ambient
    //vec3 ambient = light.ambient * material.ambient;

    //diffuse
	//vec3 norm = normalize(exNormal);
	//vec3 lightDir = normalize(light.position - exFragmentPosition); 

	//float diff = max(dot(lightDir, norm), 0.0);
	//vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//specular
	//vec3 viewDir = normalize(ViewPosition - exFragmentPosition);
	//vec3 reflectDir = reflect(-lightDir, norm);

	//vec3 halfwayDir = normalize(lightDir + viewDir);

	//float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
	//vec3 specular = light.specular * (spec * material.specular);

	//vec3 result = (ambient + diffuse + specular) /*+ material.emissive*/;
	//FragmentColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient * material.ambient;
    vec3 diffuse  = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient * material.ambient;
    vec3 diffuse  = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}