#version 420 core

layout(location = 0) in vec4 vertexPos;
layout(location = 3) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUv;
layout(location = 4) in vec4 vertexBoneWeight;
layout(location = 5) in vec4 vertexBoneIndex;

uniform mat4 model;
uniform mat4 skinningMatrices[120];

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

layout (std140, binding = 2, row_major) uniform Skinning
{
	mat4 mats[150];
} skinning;

out VertexData
{
	vec3 color;
	vec3 normal;
	vec2 uv;
} outData;

void main()
{
	vec4 pos =  		(vertexBoneWeight.x * (skinning.mats[int(vertexBoneIndex.x)] * vertexPos)) +
						(vertexBoneWeight.y * (skinning.mats[int(vertexBoneIndex.y)] * vertexPos)) +
						(vertexBoneWeight.z * (skinning.mats[int(vertexBoneIndex.z)] * vertexPos)) +
						(vertexBoneWeight.w * (skinning.mats[int(vertexBoneIndex.w)] * vertexPos));

//	vec4 pos = skinning.mats[4] * vertexPos;

	gl_Position = camera.viewPerspective * model * vec4(pos.xyz, 1.f);
	outData.normal = vertexNormal;
	outData.uv = vertexUv;
}