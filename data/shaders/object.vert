#version 450 core

// ----------------------------------------------------------------------------
// Input Variables
// ----------------------------------------------------------------------------
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coord;

// The UBO with camera data.	
layout (std140, binding = 0) uniform CameraBuffer
{
	mat4 projection;		// The projection matrix.
	mat4 cam_model;				// The model matrix - TODO: change to the view
	vec3 eye_position;		// The position of the eye in world space.
};

// The UBO with the model data.
layout (std140, binding = 1) uniform ModelData
{
	mat4 model;			// The model matrix.
};

// ----------------------------------------------------------------------------
// Output Variables
// ----------------------------------------------------------------------------
out VertexData
{
	vec3 position_ws;	  // The vertex position in world space.
	vec3 position_vs;	  // The fragmet position in view space.
    vec4 position_cs;    // The fragment position in clip space.
	vec3 normal_ms;		  // The vertex normal in model space.
	vec3 normal_ws;		  // The vertex normal in world space.
	vec2 tex_coord;		  // The vertex texture coordinates.
} out_data;

// ----------------------------------------------------------------------------
// Main Method
// ----------------------------------------------------------------------------
void main()
{
	mat4 view = inverse(cam_model);

	vec4 position_ws = model * vec4(position, 1);
	vec4 position_vs = view * position_ws;
	
	out_data.position_ws = position_ws.xyz / position_ws.w;
	out_data.position_vs = position_vs.xyz / position_vs.w;
	out_data.position_cs = projection * position_vs; 
	out_data.normal_ms = normal;
	out_data.normal_ws = transpose(inverse(mat3(model))) * normal;
	out_data.tex_coord = tex_coord;
	gl_Position = out_data.position_cs;
}