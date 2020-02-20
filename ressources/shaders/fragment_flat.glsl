#version 400 core
out vec4 frag_color;

in vec3 frag_pos;
flat in vec3 frag_col;

uniform vec3 object_color;

void main()
{
	frag_color = vec4(frag_col, 1.0);
}