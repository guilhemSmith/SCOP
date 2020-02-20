#version 400 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 t_pos;

out vec3 frag_pos;
flat out vec3 frag_col;
out vec2 text_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	frag_pos = vec3(view * model * vec4(a_pos, 1.0));
	text_pos = t_pos;
	gl_Position = projection * view * model * vec4(a_pos, 1.0);

    float r, g, b;
    r = 1 - t_pos.x - t_pos.y;
    g = t_pos.x;
    b = t_pos.y;
    frag_col = vec3(r, g, b);
}