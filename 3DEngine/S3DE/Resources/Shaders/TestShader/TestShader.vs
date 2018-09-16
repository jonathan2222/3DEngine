#version 330

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertNormal;

out vec3 fragPos;
out vec3 fragNormal;
out mat4 fragWorld;

uniform mat4 world;
uniform mat4 vp;

void main()
{
	fragWorld = world;
	gl_Position = vp*world*vec4(vertPos, 1.0);
	fragPos = (world*vec4(vertPos, 1.0)).xyz;
	fragNormal = (world*vec4(vertNormal, 0.0)).xyz;
}