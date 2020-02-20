/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:44:02 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/20 14:38:22 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# define GL_SILENCE_DEPRECATION

# define FOV_DEF 45
# define WIDTH_DEF 800
# define HEIGHT_DEF 600
# define TEXTURE_PATH_RELATIVE "ressources/textures/cat.ppm"
# define VERTEX_ULTIMATE "ressources/shaders/vertex_ultimate.glsl"
# define FRAGMENT_ULTIMATE "ressources/shaders/fragment_ultimate.glsl"

# ifndef DEP
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
# endif

# include "renderer.h"

typedef struct		s_timer
{
	float	last;
	float	current;
}					t_timer;

unsigned int		load_shader(unsigned int *shader_program, \
	const char *vertex_path, const char *fragment_path);
unsigned int		load_object(t_obj_render *obj, int argc, char *argv[]);
unsigned int		load_texture(unsigned int *texture, const char *filepath);
void				process_input(GLFWwindow *window, float camera_pos[3], \
	t_render_config *config, float delta_time);

void				shader_set_int(unsigned int shader, const char *field, \
	int value);

#endif
