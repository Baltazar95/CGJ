#version 330 core

in vec3 exNormal;
in vec3 FragPos;

out vec4 FragmentColor;

//TODO: pass these values from the engine
/*uniform*/ vec3 viewPosition = vec3(0.0, 0.0, -20.0);
uniform vec3 LightPos;

//TODO: pass these values from the engine
/*uniform*/ vec3 objectColor = vec3(0.5, 0.5, 1.0);
/*uniform*/ vec3 lightColor = vec3(1.0);

float specularIntensity = 0.5;

void main(void)
{
	vec3 norm = normalize(exNormal);
	vec3 lightDir = normalize(LightPos - FragPos); 

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularIntensity * spec * lightColor;

	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    //TODO: tweak specular lighting
	vec3 result = (ambient + diffuse /*+ specular*/) * objectColor;
	FragmentColor = vec4(result, 1.0);
}