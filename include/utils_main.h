/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:03:24 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/09 17:48:43 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_MAIN_H
# define UTILS_MAIN_H

# ifndef DEP
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
# endif

int					close_soft(int exit_code, unsigned int *shader_program);
void				framebuffer_size_callback(GLFWwindow *window, \
	int width, int height);

#endif
