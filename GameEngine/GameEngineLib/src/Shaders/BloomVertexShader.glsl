#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

out vec3 exFragmentPosition;
out vec3 exNormal;
out vec2 exTexcoord;

uniform mat4 NormalMatrix;
uniform mat4 ModelMatrix;
uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(void)
{
	exFragmentPosition = vec3(ModelMatrix * vec4(inPosition, 1.0));
	exNormal = normalize(mat3(NormalMatrix) * inNormal);
	exTexcoord = inTexcoord;
	gl_Position = ProjectionMatrix * ViewMatrix * vec4(exFragmentPosition, 1.0);
}