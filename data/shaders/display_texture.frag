#version 450 core

// ----------------------------------------------------------------------------
// Input Variables
// ----------------------------------------------------------------------------
in VertexData
{
	vec2 tex_coord;  // The vertex texture coordinates.
} in_data;

// The texture to be shown.
layout (binding = 0) uniform sampler2D input_texture;

// ----------------------------------------------------------------------------
// Output Variables
// ----------------------------------------------------------------------------
layout (location = 0) out vec4 final_color;

// ----------------------------------------------------------------------------
// Main Method
// ----------------------------------------------------------------------------
void main()
{
    final_color = texture(input_texture, in_data.tex_coord);
}