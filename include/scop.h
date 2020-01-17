/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:44:02 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/17 11:10:36 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# define GL_SILENCE_DEPRECATION

# define FOV_DEF 45
# define WIDTH_DEF 800
# define HEIGHT_DEF 600
# define TEXTURE_PATH_RELATIVE "ressources/textures/honest.ppm"
# define VERTEX_FLAT "ressources/shaders/vertex_flat.glsl"
# define FRAGMENT_FLAT "ressources/shaders/fragment_flat.glsl"
# define VERTEX_LIGHT "ressources/shaders/vertex_light.glsl"
# define FRAGMENT_LIGHT "ressources/shaders/fragment_light.glsl"
# define VERTEX_TEXTURE "ressources/shaders/vertex_texture.glsl"
# define FRAGMENT_TEXTURE "ressources/shaders/fragment_texture.glsl"

# ifndef DEP
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
# endif

typedef struct		s_timer
{
	float	last;
	float	current;
}					t_timer;

unsigned int		load_shader(unsigned int *shader_program, \
	const char *vertex_path, const char *fragment_path);
unsigned int		load_object(void);
unsigned int		load_texture(unsigned int *texture, const char *filepath);
void				process_input(GLFWwindow *window, float camera_pos[3], \
	t_render_config *config, float delta_time);

void				shader_set_int(unsigned int shader, const char *field, \
	int value);

#endif
