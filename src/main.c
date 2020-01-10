/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:43:48 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/10 17:47:51 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "libft.h"
#include "utils_main.h"
#include <math.h>

int					main(void)
{
	GLFWwindow		*window;
	unsigned int	shader_program;
	unsigned int	vao;
	unsigned int	texture;

	if ((window = init_opengl()) == NULL)
		return (-1);
	if (load_shader(&shader_program))
		return (close_soft(-1, NULL));
	load_texture(&texture, "ressources/textures/lies_ascii.ppm");
	(void)vao;
	// if (!(vao = load_object()))
	// 	return (close_soft(-1, &shader_program));
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		// process_render(shader_program, vao, texture);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return (close_soft(0, &shader_program));
}

static GLFWwindow	*init_opengl(void)
{
	GLFWwindow	*window;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	window = glfwCreateWindow(WIDTH_DEF, HEIGHT_DEF, "SCOP", NULL, NULL);
	if (window == NULL)
	{
		ft_putendl_fd("Failed to create GLFW window", 2);
		glfwTerminate();
		return (NULL);
	}
	glfwMakeContextCurrent(window);
	if (GLEW_OK != glewInit())
	{
		ft_putendl_fd("Failed to init GLEW:", 2);
		glfwSetWindowShouldClose(window, 1);
		return (NULL);
	}
	glViewport(0, 0, WIDTH_DEF, HEIGHT_DEF);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	return (window);
}

static void			process_input(GLFWwindow *window)
{
	static int		wireframe = 0;
	static int		flag = 0;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS && flag == 0)
	{
		flag = 1;
		if (!wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		wireframe = !wireframe;
	}
	if (flag == 1 && glfwGetKey(window, GLFW_KEY_COMMA) != GLFW_PRESS)
	{
		flag = 0;
	}
}

// static void			process_render(unsigned int shaders, unsigned int vao, unsigned int texture)
// {
// 	(void)shaders;
// 	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	glActiveTexture(GL_TEXTURE0);
// 	glBindTexture(GL_TEXTURE_2D, texture);
// 	glUseProgram(shaders);
// 	glBindVertexArray(vao);
// 	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
// 	glBindVertexArray(0);
// }
