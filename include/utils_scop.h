/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_scop.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:03:24 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/06 14:05:17 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_SCOP_H
# define UTILS_SCOP_H

# ifndef DEP
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
# endif

int					close_soft(int exit_code, t_render_config config, \
	t_obj_render obj);
void				framebuffer_size_callback(GLFWwindow *window, \
	int width, int height);

#endif
