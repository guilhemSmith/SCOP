/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:02:53 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/09 17:47:45 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEP
# include <GL/glew.h>
# include <GLFW/glfw3.h>
#endif

void				framebuffer_size_callback(GLFWwindow *window, \
	int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

int					close_soft(int exit_code, unsigned int *shader_program)
{
	if (shader_program)
		glDeleteProgram(*shader_program);
	glfwTerminate();
	return (exit_code);
}
