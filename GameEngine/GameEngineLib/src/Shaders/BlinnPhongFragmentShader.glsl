#version 330 core

in vec3 exNormal;
in vec3 FragPos;

out vec4 FragmentColor;

uniform vec3 LightPos;

/*uniform*/ vec3 objectColor = vec3(0.5, 0.5, 1.0);
/*uniform*/ vec3 lightColor = vec3(1.0);

void main(void)
{
	vec3 norm = normalize(exNormal);
	vec3 lightDir = normalize(LightPos - FragPos); 

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;
	FragmentColor = vec4(result, 1.0);
}