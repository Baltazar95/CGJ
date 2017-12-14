#version 330 core

in vec3 exFragmentPosition;
in vec3 exNormal;
in vec2 exTexcoord;

out vec4 FragmentColor;

//TODO: pass these values from the engine
uniform vec3 viewPosition = vec3(0.0, 0.0, 20.0);

struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emissive;

    float shininess;
};  
uniform Material material;

struct Light 
{
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform sampler2D tex;

void main(void)
{
	//ambient
    vec3 ambient = light.ambient * material.ambient;

    //diffuse
	vec3 norm = normalize(exNormal);
	vec3 lightDir = normalize(light.position - exFragmentPosition); 

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//specular
	vec3 viewDir = normalize(viewPosition - exFragmentPosition);
	vec3 reflectDir = reflect(-lightDir, norm);

	vec3 halfwayDir = normalize(lightDir + viewDir);

	float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = (ambient + diffuse + specular) + material.emissive;
	//FragmentColor = vec4(result, 1.0);
	FragmentColor = texture(tex, exTexcoord) * vec4(result, 1.0);
}