#version 420 core

layout(location = 0) in vec4 vertexPos;
layout(location = 3) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUv;

uniform mat4 model;


layout (std140, binding = 0, row_major) uniform CameraSettings
{
							// Base Alignment  	// Aligned Offset
	vec3 position;			// 16			   	// 0
	vec3 direction; 		// 16				// 16
	mat4 viewPerspective;	// 64				// 32
} camera;

layout (std140, binding = 1) uniform Lights
{
							// Base Alignment  	// Aligned Offset
	vec4 position;			// 16				// 0
	vec3 direction; 		// 16				// 16
} lights;

out VertexData
{
	vec3 color;
	vec3 normal;
	vec2 uv;
} outData;

void main()
{
	gl_Position = camera.viewPerspective * model * vec4(vertexPos.xyz, 1.f);
	outData.normal = vertexNormal;
	outData.uv = vertexUv;
}