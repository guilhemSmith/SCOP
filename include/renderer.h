/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:28:06 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/16 16:21:35 by gsmith           ###   ########.fr       */
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
	unsigned int	shader;
	unsigned int	fov;
	unsigned int	width;
	unsigned int	height;
	int				wireframe;
	int				w_flag;
	int				texture;
	int				t_flag;
}				t_render_config;

typedef struct	s_obj_render {
	unsigned int	vao;
	unsigned int	texture;
	unsigned int	mode;
	unsigned int	start;
	unsigned int	count;
}				t_obj_render;

void			render_object(t_render_config config, t_obj_render object, \
	const float camera_pos[3]);

#endif
