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

    float level;
	if (gl_VertexID % 2 == 1)
		level = (gl_VertexID % 8) * 0.125;
	else
		level = 1 - ((gl_VertexID % 8) * 0.125);
    frag_col = vec3(level, level, level);
}