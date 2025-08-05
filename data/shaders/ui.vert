#version 450 core

// ----------------------------------------------------------------------------
// Local Variables
// ----------------------------------------------------------------------------
// Texture coordinates for the quad.
const vec2 tex_coords[4] = vec2[4] (
	vec2(0.0, 0.0),
	vec2(1.0, 0.0),
	vec2(0.0, 1.0),
    vec2(1.0, 1.0)
);

const vec2 vertex_coords[4] = vec2[4] (
	vec2(-0.5f, -0.5f),
	vec2(0.5f, -0.5f),
	vec2(-0.5f, 0.5f),
    vec2(0.5f, 0.5f)
);

// ----------------------------------------------------------------------------
// Input Variables
// ----------------------------------------------------------------------------
layout (location = 0) uniform float screenSizeRatio; // Screen size in pixels

// The UBO with the model data.
layout (std140, binding = 0) uniform Transform
{
	vec2 pivot;         // Pivot position (0 => left top, 1 => right bottom)
    vec2 pivot_offset;  // Pivot offset in the element (0 => middle)
    vec2 size;          // Size of the element (y=1 => window height)
    bool xRelativeToY;  // Compute x size relative to size y or to the screen coordinates
};

// The UBO definig region of texture to be rendered
// Rectangle (0,0)-(1,1) is whole texture.
layout (std140, binding = 1) uniform Subtexture
{
    vec2 min_corner;
    vec2 max_corner;
} subtexture;

// ----------------------------------------------------------------------------
// Output Variables
// ----------------------------------------------------------------------------
out VertexData
{
    vec2 tex_coord; // The vertex texture coordinates.
} out_data;

// ----------------------------------------------------------------------------
// Main Method
// ----------------------------------------------------------------------------
void main()
{
	vec2 vertex_coord = vertex_coords[gl_VertexID];
    
    // Aply pivot offset
    vertex_coord -= pivot_offset / 2;
    
    // Aply scale
    vertex_coord.y *= size.y;
    if (xRelativeToY)
    {
        vertex_coord.x *= size.x / screenSizeRatio;
    }
    else 
    {
        vertex_coord.x *= size.x;
    }

    // Aply pivot position
    vertex_coord += pivot;

    // Transform to ndc
    vertex_coord = vertex_coord * 2 - 1;

    // Compute texture coords
    vec2 subtexture_delta = subtexture.max_corner - subtexture.min_corner;
    out_data.tex_coord = subtexture.min_corner + subtexture_delta * tex_coords[gl_VertexID];

    gl_Position = vec4(vertex_coord, 0, 1);
}