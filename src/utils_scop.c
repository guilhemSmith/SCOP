/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_scop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:02:53 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/17 12:33:14 by gsmith           ###   ########.fr       */
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
	if (config.shader[0])
		glDeleteProgram(config.shader[0]);
	if (config.shader[1])
		glDeleteProgram(config.shader[1]);
	if (config.shader[2])
		glDeleteProgram(config.shader[2]);
	if (obj.texture)
		glDeleteTextures(1, &(obj.texture));
	if (obj.vao)
		glDeleteVertexArrays(1, &(obj.vao));
	if (obj.vbo)
		glDeleteBuffers(1, &(obj.vbo));
	glfwTerminate();
	return (exit_code);
}
