#version 400 core
out vec4 frag_color;

in vec3 frag_pos;
flat in vec3 frag_col;
in vec2 text_pos;

uniform sampler2D texture_color;
uniform float alpha;

void main()
{
	frag_color = vec4(frag_col, 1.0) * (1.0 - alpha);
	frag_color += texture(texture_color, text_pos) * alpha;
}