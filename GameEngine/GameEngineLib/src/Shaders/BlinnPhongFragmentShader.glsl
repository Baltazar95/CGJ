#version 330 core

in vec3 exFragmentPosition;
in vec3 exNormal;
/*in vec2 exTexcoord;*/

out vec4 FragmentColor;

//TODO: pass these values from the engine
uniform vec3 viewPosition = vec3(0.0, 0.0, -20.0);
uniform vec3 LightPos;

//TODO: pass these values from the engine
uniform vec3 objectColor = vec3(0.5, 0.5, 1.0);
uniform vec3 lightColor = vec3(1.0);

void main(void)
{
	//ambient
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    //diffuse
	vec3 norm = normalize(exNormal);
	vec3 lightDir = normalize(LightPos - exFragmentPosition); 

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	//specular
	float specularStrength = 0.5;

	vec3 viewDir = normalize(viewPosition - exFragmentPosition);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (/*ambient + diffuse +*/ specular) * objectColor;
	FragmentColor = vec4(result, 1.0);
}