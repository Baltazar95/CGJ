#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

out vec3 exFragmentPosition;
out vec3 exNormal;
out vec4 clipSpace;
out vec3 toCameraVector;
out vec2 exTexcoord;

uniform mat4 NormalMatrix;
uniform mat4 ModelMatrix;
uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main()
{
    vec4 worldPosition = ModelMatrix * vec4(inPosition, 1.0);
    clipSpace = ProjectionMatrix * ViewMatrix * worldPosition;
    gl_Position = clipSpace;
    toCameraVector = inPosition - worldPosition.xyz;
    exTexcoord = vec2(inTexcoord.x/2.0 + 0.5, inTexcoord.y/2.0 + 0.5);
}