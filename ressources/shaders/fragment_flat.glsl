#version 400 core
out vec4 frag_color;

flat in vec3 frag_pos;
in vec3 normal;

uniform vec3 object_color;
uniform vec3 light_color;
uniform vec3 light_pos;

void main()
{
	float ambient_strength = 0.3;
	vec3 ambient = ambient_strength * light_color;

	vec3 norm = normalize(normal);
	vec3 light_dir = normalize(light_pos - frag_pos);
	float diff = max(dot(norm, light_dir), 0.0);
	vec3 diffuse = diff * light_color;

	vec3 result = (ambient + diffuse) * object_color;
	frag_color = vec4(result, 1.0);
}