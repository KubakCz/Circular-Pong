#version 450 core

// ----------------------------------------------------------------------------
// Input Variables
// ----------------------------------------------------------------------------
in VertexData
{
	vec3 position_ws;	  // The vertex position in world space.
	vec3 position_vs;	  // The fragmet position in view space.
    vec4 position_cs;    // The fragment position in clip space.
	vec3 normal_ms;		  // The vertex normal in model space.
	vec3 normal_ws;		  // The vertex normal in world space.
	vec2 tex_coord;		  // The vertex texture coordinates.
} in_data;

layout (std140, binding = 0) uniform CameraBuffer
{
	mat4 projection;		// The projection matrix.
	mat4 cam_model;			// The model matrix - TODO: change to the view
	vec3 eye_position;		// The position of the eye in world space.
};

layout (location = 0) uniform bool use_mask;

// binding 1 for consistency with lit shaders
layout (binding = 1) uniform sampler2D mask_texture; // alpha in r, depth (ndc) in g

layout (location = 2) uniform float min_z_for_alpha_ws;

// ----------------------------------------------------------------------------
// Output Variables
// ----------------------------------------------------------------------------
// Position of the fragment in view space. (Used in SSAO)
// In case of blending, if mix ratio is < 1, original position is kept, else new position is writen.
layout (location = 0) out vec4 position_vs;
// Position of the fragment in view space.
// In case of blending, if alpha < 1, original normal is kept.
layout (location = 1) out vec4 normal_vs;

// ----------------------------------------------------------------------------
// Main Method
// ----------------------------------------------------------------------------
void main()
{
    // Compute the alpha according to mask.
    vec2 screen_coord = ((in_data.position_cs.xy / in_data.position_cs.w) + 1) * 0.5;
    float depth = in_data.position_vs.z;
    float alpha = (use_mask && texture(mask_texture, screen_coord).g > depth && in_data.position_ws.z <= min_z_for_alpha_ws) ? texture(mask_texture, screen_coord).r : 1;

    // Compute the final view space position
    position_vs = vec4(in_data.position_vs, alpha < 1 ? 0 : 1);

    // Copmpute the final view space normal
    mat4 view = inverse(cam_model);
    normal_vs = vec4(transpose(inverse(mat3(view))) * in_data.normal_ws, alpha < 1 ? 0 : 1);
}

