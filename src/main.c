/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:43:48 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/08 16:58:47 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void				framebuffer_size_callback(GLFWwindow *window, \
						int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

static GLFWwindow	*init_opengl(void)
{
	GLFWwindow	*window;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	window = glfwCreateWindow(HEIGHT_DEF, WIDTH_DEF, "Hello World", NULL, NULL);
	if (window == NULL)
	{
		ft_putendl_fd("Failed to create GLFW window", 2);
		glfwTerminate();
		return (NULL);
	}
	glfwMakeContextCurrent(window);
	glViewport(0, 0, HEIGHT_DEF, WIDTH_DEF);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	return (window);
}

static void			process_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
}

static void			process_render(GLFWwindow *window)
{
	(void)window;
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

int					main(void)
{
	GLFWwindow	*window;

	if ((window = init_opengl()) == NULL)
		return (-1);
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		process_render(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return (0);
}
