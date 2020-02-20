/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_scop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:02:53 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/20 14:40:53 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEP
# include <GL/glew.h>
# include <GLFW/glfw3.h>
#endif

#include "renderer.h"

void				framebuffer_size_callback(GLFWwindow *window, \
	int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

int					close_soft(int exit_code, t_render_config config, \
	t_obj_render obj)
{
	if (config.shader)
		glDeleteProgram(config.shader);
	if (obj.texture)
		glDeleteTextures(1, &(obj.texture));
	if (obj.vao)
		glDeleteVertexArrays(1, &(obj.vao));
	if (obj.vbo)
		glDeleteBuffers(1, &(obj.vbo));
	glfwTerminate();
	return (exit_code);
}
