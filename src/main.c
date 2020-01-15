/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:43:48 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/15 18:01:17 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "libft.h"
#include "utils_main.h"
#include "matrix.h"
#include <math.h>
#include "vector.h"
#include <stdio.h>

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
	if (!(vao = load_object()))
		return (close_soft(-1, &shader_program));
	// load_texture(&texture, "ressources/textures/toast.ppm");
	// load_texture(&texture, "ressources/textures/honest.ppm");
	load_texture(&texture, "ressources/textures/lies_ascii.ppm");
	// load_texture(&texture, "ressources/textures/lies_raw.ppm");
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		process_render(shader_program, vao, texture);
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

static void			process_render(unsigned int shaders, unsigned int vao, unsigned int texture)
{
	float			model[16];
	float			view[16];
	float			projection[16];

	mat4_set_diagonal(model, 1);
	mat4_rotate(model, (float)glfwGetTime(), (const float[3]){0.5, 1, 0});
	mat4_set_diagonal(view, 1);
	mat4_translate(view, (const float[3]){0, 0, -3});
	mat4_perspective(45, WIDTH_DEF / HEIGHT_DEF, (float[2]){0.1, 100}, projection);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUseProgram(shaders);
	glUniformMatrix4fv(glGetUniformLocation(shaders, "model"), 1, GL_FALSE, model);
	glUniformMatrix4fv(glGetUniformLocation(shaders, "view"), 1, GL_FALSE, view);
	glUniformMatrix4fv(glGetUniformLocation(shaders, "projection"), 1, GL_FALSE, projection);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
