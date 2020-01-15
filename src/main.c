/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:43:48 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/15 15:36:46 by gsmith           ###   ########.fr       */
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
	// load_texture(&texture, "ressources/textures/toast.ppm");
	// load_texture(&texture, "ressources/textures/honest.ppm");
	load_texture(&texture, "ressources/textures/lies_ascii.ppm");
	// load_texture(&texture, "ressources/textures/lies_raw.ppm");
	if (!(vao = load_object()))
		return (close_soft(-1, &shader_program));
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

static void			mat4_print(const float mat[16])
{
	printf("\n%3f, %3f, %3f, %3f\n%3f, %3f, %3f, %3f\n%3f, %3f, %3f, %3f\n%3f, %3f, %3f, %3f\n", \
		mat[0], mat[1], mat[2], mat[3], mat[4], mat[5], mat[6], mat[7], \
		mat[8], mat[9], mat[10], mat[11], mat[12], mat[13], mat[14], mat[15]);
}

static void			process_render(unsigned int shaders, unsigned int vao, unsigned int texture)
{
	float			transf[16];

	mat4_set_diagonal(transf, 1);
	printf("loop\n");
	mat4_print(transf);
	mat4_translate(transf,(const float[3]){0.5, -0.5, 0});
	mat4_rotate(transf, (float)glfwGetTime(), (const float[3]){1, 0, 0});
	mat4_scale(transf, (const float[3]){0.8, 0.8, 0.8});
	mat4_print(transf);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUseProgram(shaders);
	glUniformMatrix4fv(glGetUniformLocation(shaders, "transform"), 1, GL_FALSE, transf);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
