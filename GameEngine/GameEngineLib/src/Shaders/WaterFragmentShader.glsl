#version 330 core

in vec3 exFragmentPosition;
in vec3 exNormal;
in vec4 clipSpace;
in vec3 toCameraVector;
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
uniform sampler2D dudvMap;
uniform float moveFactor;

void main()
{
    vec2 ndc = (clipSpace.xy/ clipSpace.w)/2.0 + 0.5;
    vec2 reflectionCoords = vec2(-ndc.x, ndc.y);
    vec2 distortion1 = (texture(dudvMap, vec2(exTexcoord.x + moveFactor, exTexcoord.y)).rg*2.0 - 1.0) * 0.02;
    vec2 distortion2 = (texture(dudvMap, vec2(-exTexcoord.x + moveFactor, exTexcoord.y + moveFactor)).rg*2.0 - 1.0) * 0.02;
    vec2 totaldistortion = distortion1 + distortion2;
    reflectionCoords += totaldistortion;

    
    reflectionCoords.x = clamp(reflectionCoords.x, -0.999, -0.001);
    reflectionCoords.y = clamp(reflectionCoords.y, 0.001, 0.999);


    vec3 viewVector = normalize(toCameraVector);
    float reflectiveFactor = pow(dot(viewVector, vec3(0.0, 1.0, 0.0)), 0.5);

    vec4 col = texture(tex, reflectionCoords);
    FragmentColor = mix(col, vec4(0.1, 0.1, 0.8, 0.0), reflectiveFactor);
}