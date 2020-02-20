#version 400 core
out vec4 frag_color;

in vec3 frag_pos;
flat in vec3 frag_col;

void main()
{
	frag_color = vec4(frag_col, 1.0);
}