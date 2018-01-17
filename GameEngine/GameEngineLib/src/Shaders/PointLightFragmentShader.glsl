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

void main()
{
    FragColor = vec4(diffuse, 1.0); // set alle 4 vector values to 1.0
}