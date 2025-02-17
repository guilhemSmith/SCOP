/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:28:06 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/21 16:18:16 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# define CAMERA_SPEED

# ifndef DEP
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
# endif

# define ROT_X 0.0
# define ROT_Y 1.0
# define ROT_Z 0.0

typedef struct	s_render_config {
	unsigned int	shader;
	unsigned int	fov;
	unsigned int	width;
	unsigned int	height;
	unsigned int	texture;
	int				wireframe;
	int				w_flag;
	float			current_alpha;
	float			target_alpha;
	int				alpha_flag;
}				t_render_config;

typedef struct	s_obj_render {
	unsigned int	vao;
	unsigned int	vbo;
	unsigned int	ebo;
	unsigned int	nb_elem;
	unsigned int	texture;
	unsigned int	mode;
	unsigned int	start;
	unsigned int	count;
}				t_obj_render;

void			render_object(t_render_config *config, t_obj_render *object, \
	const float camera_pos[3]);
void			shader_set_vec3(unsigned int shader, const char *field, \
	const float vec[3]);
void			shader_set_mat4(unsigned int shader, const char *field, \
	const float mat[16]);

#endif
