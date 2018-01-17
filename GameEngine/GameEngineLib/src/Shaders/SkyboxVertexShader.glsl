#version 330 core

in vec3 inPosition;
in vec3 inTexcoord;
in vec3 inNormal;

out vec3 exFragmentPosition;
out vec3 exNormal;
out vec3 exTexcoord;

uniform mat4 NormalMatrix;
uniform mat4 ModelMatrix;
uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(void)
{
	gl_Position = ProjectionMatrix * ModelMatrix * vec4(inPosition, 1.0);
	exTexcoord = inTexcoord;
}