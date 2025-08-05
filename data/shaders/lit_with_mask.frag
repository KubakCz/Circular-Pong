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

layout (std140, binding = 2) uniform MaterialBuffer
{
    vec3 ambient;
    bool has_texture;
    vec3 diffuse;
    float alpha;
    vec3 specular;
    float shininess;
} material;

struct Light
{
    vec4 position;      // The position of the light in ws. w = 1 for standard light, w = 0 for sun.
    vec3 ambient;       // The ambient component of light.
    vec3 diffuse;       // The diffuse component of light.
    vec3 specular;      // The specular component of light.
};

layout(std430, binding = 3) buffer Lights {
    int lightsSize;
    Light[] lights;
};

layout (location = 0) uniform bool use_mask;
layout (location = 1) uniform bool use_ssao;

layout (binding = 0) uniform sampler2D diffuse_texture;
layout (binding = 1) uniform sampler2D mask_texture; // alpha in r, depth (vs) in g
layout (binding = 2) uniform sampler2D ssao_texture;

layout (location = 2) uniform float min_z_for_alpha_ws;

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
    // Based on lit shader from PV227 lecture_07

    // Computes the lighting.
	vec3 N = normalize(in_data.normal_ws);
	vec3 V = normalize(eye_position - in_data.position_ws);

    vec3 amb = vec3(0);
    vec3 dif = vec3(0);
    vec3 spe = vec3(0);  

    for (int i = 0; i < lightsSize; ++i) {
        vec3 L_not_normalized = lights[i].position.xyz - in_data.position_ws * lights[i].position.w;
        vec3 L = normalize(L_not_normalized);
        vec3 H = normalize(L + V);

        // Calculates the basic Phong factors.
        float Iamb = 1.0;
        float Idif = max(dot(N, L), 0.0);
        float Ispe = (Idif > 0.0) ? pow(max(dot(N, H), 0.0), material.shininess) : 0.0;

        // Calculates attenuation
        if (lights[i].position.w != 0.0)
        {
            float distance_from_light = length(L_not_normalized);
            float atten_factor = 1.0 / (distance_from_light * distance_from_light);

            Iamb *= atten_factor;
            Idif *= atten_factor;
            Ispe *= atten_factor;
        }

        // Applies the factors to light color.
        amb += Iamb * lights[i].ambient;
        dif += Idif * lights[i].diffuse;
        spe += Ispe * lights[i].specular;  
    } 

	// Computes the material.
	vec3 mat_ambient = material.ambient;
	vec3 mat_diffuse = material.diffuse;
	vec3 mat_specular = material.specular;

    if (material.has_texture) 
    {
        vec3 tex_col = texture(diffuse_texture, in_data.tex_coord).rgb;
        mat_ambient *= tex_col;
        mat_diffuse *= tex_col;
    }

    // Compute position of the fragment on the screen
    vec2 screen_coord = ((in_data.position_cs.xy / in_data.position_cs.w) + 1) * 0.5;

    // Get ssao
    float ssao = texture(ssao_texture, screen_coord).r;

	// Computes the final light color.
	vec3 final_light = mat_ambient * amb * ssao + mat_diffuse * dif + material.specular * spe;

	// Compute the alpha according to mask.
    float depth = in_data.position_vs.z;
    float alpha = (use_mask && texture(mask_texture, screen_coord).g > depth && in_data.position_ws.z <= min_z_for_alpha_ws) ? texture(mask_texture, screen_coord).r : 1;

    // Compute the final color
	final_color = vec4(final_light, material.alpha * alpha);
}