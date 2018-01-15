#version 330 core

in vec3 exFragmentPosition;
in vec3 exNormal;
in vec4 clipSpace;
in vec3 toCameraVector;

out vec4 FragmentColor;

//TODO: pass these values from the engine
uniform vec3 viewPosition;

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

void main()
{
    vec2 ndc = (clipSpace.xy/ clipSpace.w)/2.0 + 0.5;
    vec2 reflectionCoords = vec2(-ndc.x, ndc.y);
    vec4 col = texture(tex, reflectionCoords);

    vec3 viewVector = normalize(toCameraVector);
    float reflectiveFactor = pow(dot(viewVector, vec3(0.0, 1.0, 0.0)), 0.5);

    FragmentColor = mix(col, vec4(0.0, 0.0, 1.0, 0.0), reflectiveFactor);
}