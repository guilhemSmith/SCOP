#version 400 core
out vec4 frag_color;

flat in vec3 frag_pos;

uniform vec3 object_color;

void main()
{
	frag_color = vec4(object_color, 1.0);
}