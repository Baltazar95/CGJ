#version 330 core

in vec3 exFragmentPosition;
in vec3 exNormal;
in vec2 exTexcoord;

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

void main(void)
{
	FragmentColor =  texture(tex, exTexcoord) * vec4(1.0);
}