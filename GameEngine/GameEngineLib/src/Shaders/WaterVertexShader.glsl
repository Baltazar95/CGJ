#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

out vec3 exFragmentPosition;
out vec3 exNormal;
out vec4 clipSpace;

uniform mat4 NormalMatrix;
uniform mat4 ModelMatrix;
uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main()
{
    clipSpace = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(inTexcoord.x, inTexcoord.y, 0.0, 1.0);
    gl_Position = clipSpace;
}