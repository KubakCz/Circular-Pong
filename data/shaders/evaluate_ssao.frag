#version 450 core

// The number of the samples.
#define NUMBER_OF_SSAO_SAMPLES 128

// ----------------------------------------------------------------------------
// Input Variables
// ----------------------------------------------------------------------------
in VertexData
{
	vec2 tex_coord;  // The vertex texture coordinates.
} in_data;

layout (std140, binding = 0) uniform CameraBuffer
{
	mat4 projection;		// The projection matrix.
	mat4 cam_model;			// The model matrix - TODO: change to the view
	vec3 eye_position;		// The position of the eye in world space.
};

// The random positions of the SSAO kernel.
layout (std140, binding = 1) uniform KernelSamples
{
	vec4 kernel_samples[NUMBER_OF_SSAO_SAMPLES];
};

// The texture with positoins in view space.
layout (binding = 0) uniform sampler2D positions_vs_tex;
// The texture with normals in view space.
layout (binding = 1) uniform sampler2D normals_vs_tex;
// The texture with random tangents in view space.
layout (binding = 2) uniform sampler2D random_tangent_vs_tex;

// The radius of the SSAO hemisphere which is sampled.
layout (location = 0) uniform float ssao_radius;

// ----------------------------------------------------------------------------
// Output Variables
// ----------------------------------------------------------------------------
// The computed occlusion.
layout (location = 0) out float final_occlusion;

// ----------------------------------------------------------------------------
// Main Method
// ----------------------------------------------------------------------------
void main()
{
	// Based on PV227 lecture 04

	// Position and normal in view space
	vec4 position_vs = texture(positions_vs_tex, in_data.tex_coord);
	vec3 normal_vs = texture(normals_vs_tex, in_data.tex_coord).xyz;

	// Compute tangent and bitangent
    vec3 tangent_vs = texture(random_tangent_vs_tex, gl_FragCoord.xy / vec2(textureSize(random_tangent_vs_tex, 0))).xyz;
	vec3 bitangent_vs = normalize(cross(normal_vs, tangent_vs));
	tangent_vs = normalize(cross(bitangent_vs, normal_vs));

	// Transform matrix for samples
	mat3 TBN = mat3(tangent_vs, bitangent_vs, normal_vs);

	// Compute number of (not) occluded samples
	int occluded = 0, not_occluded = 0;
	for (int i = 0; i < NUMBER_OF_SSAO_SAMPLES; ++i)
	{
		// Compute position of the sample
		vec3 sample_offset_vs = TBN * kernel_samples[i].xyz * ssao_radius;
		vec3 sample_position_vs = position_vs.xyz + sample_offset_vs;
		vec4 sample_position_cs = projection * vec4(sample_position_vs, 1.0);
		vec3 sample_position_nds = sample_position_cs.xyz / sample_position_cs.w;

		vec4 closest_object_vs = textureLod(positions_vs_tex, sample_position_nds.xy * 0.5 + 0.5, 0);

		// Compare distances
		if (closest_object_vs.z == 0) // background - no occluder
		{
			not_occluded++;
		}
		else
		{
			if(sample_position_vs.z - closest_object_vs.z > ssao_radius) 
			{
				// The closest object is to far from the sample to be ocluder
				// => do not count, there still may be an occluder
			}
			else if (sample_position_vs.z > closest_object_vs.z)
			{
				// The closest object is closer to the camera than the sample
				occluded++;
			}
			else
			{
				// The closest object is farther to the camera than the sample
				not_occluded++;
			}
		}

		// Compute the final occlusion
		if (position_vs.w == 0.0) // background
			final_occlusion = 0.0;
		else if ((occluded + not_occluded) == 0) // No valid samples
			final_occlusion = 1.0;
		else
			final_occlusion = float(not_occluded) / float(occluded + not_occluded);
	}
}