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

layout (std140, binding = 2) uniform MaterialBuffer
{
    vec3 ambient;
    bool has_texture;
    vec3 diffuse;
    float alpha;
    vec3 specular;
    float shininess;
} material;

layout (binding = 0) uniform sampler2D diffuse_texture;

// ----------------------------------------------------------------------------
// Output Variables
// ----------------------------------------------------------------------------
// The final output color.
layout (location = 0) out vec4 final_color;

// ----------------------------------------------------------------------------
// Main Method
// ----------------------------------------------------------------------------
void main()
{
    final_color = vec4(texture(diffuse_texture, in_data.tex_coord).r, in_data.position_vs.z, 0, 0);
}