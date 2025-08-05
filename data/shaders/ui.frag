#version 450 core

// ----------------------------------------------------------------------------
// Input Variables
// ----------------------------------------------------------------------------
in VertexData
{
    vec2 tex_coord; // The vertex texture coordinates.
} in_data;

layout(location = 1) uniform vec4 color;
layout(binding = 0) uniform sampler2D ui_texture;

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
    final_color = texture(ui_texture, in_data.tex_coord) * color;
}