/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:28:06 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/17 12:33:20 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# define CAMERA_SPEED

# ifndef DEP
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
# endif

typedef struct	s_render_config {
	unsigned int	shader[3];
	unsigned int	fov;
	unsigned int	width;
	unsigned int	height;
	unsigned int	texture;
	int				wireframe;
	int				w_flag;
	int				shader_flag;
}				t_render_config;

typedef struct	s_obj_render {
	unsigned int	vao;
	unsigned int	vbo;
	unsigned int	texture;
	unsigned int	mode;
	unsigned int	start;
	unsigned int	count;
}				t_obj_render;

void			render_object(t_render_config config, t_obj_render object, \
	const float camera_pos[3]);
void			shader_set_vec3(unsigned int shader, const char *field, \
	const float vec[3]);
void			shader_set_mat4(unsigned int shader, const char *field, \
	const float mat[16]);

#endif
