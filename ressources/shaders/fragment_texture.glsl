#version 400 core
out vec4 frag_color;

in vec3 frag_pos;
in vec2 text_pos;

uniform sampler2D texture_color;

void main()
{
	frag_color = texture(texture_color, text_pos);
}