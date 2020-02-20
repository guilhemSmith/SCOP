#version 400 core
layout (location = 0) in vec3 a_pos;

out vec3 frag_pos;
flat out vec3 frag_col;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	frag_pos = vec3(view * model * vec4(a_pos, 1.0));
	gl_Position = projection * view * model * vec4(a_pos, 1.0);

    float r, g, b;
    r = (int(a_pos.x * 500) % 255) / 255.0f;
    g = (int(a_pos.y * 500) % 255) / 255.0f;
    b = (int(a_pos.z * 500) % 255) / 255.0f;
    frag_col = vec3(r, g, b);
}