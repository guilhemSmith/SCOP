/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:44:02 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/16 11:25:56 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# define GL_SILENCE_DEPRECATION

# define WIDTH_DEF 800
# define HEIGHT_DEF 600
# define TEXTURE_PATH_RELATIVE "ressources/textures/honest.ppm"

# ifndef DEP
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
# endif

unsigned int		load_shader(unsigned int *shader_program);
unsigned int		load_object(void);
unsigned int		load_texture(unsigned int *texture, const char *filepath);

void				shader_set_int(unsigned int shader, const char *field, \
	int value);

static GLFWwindow	*init_opengl(void);
static void			process_input(GLFWwindow *window);
static void			process_render(unsigned int shader, unsigned int vao, \
	unsigned int texture);

#endif
