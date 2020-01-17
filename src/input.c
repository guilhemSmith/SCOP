/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:40:51 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/17 11:02:21 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "renderer.h"

static void		polymode(GLFWwindow *window, unsigned int key, \
	int *state, int *flag)
{
	if (glfwGetKey(window, key) == GLFW_PRESS && *flag == 0)
	{
		*flag = 1;
		if (!*state)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		*state = !*state;
	}
	if (*flag == 1 && glfwGetKey(window, key) != GLFW_PRESS)
		*flag = 0;
}

static void		select_shader(GLFWwindow *window, t_render_config *conf)
{
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && conf->shader_flag != 0)
		conf->shader_flag = 0;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && conf->shader_flag != 1)
		conf->shader_flag = 1;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && conf->shader_flag != 2)
		conf->shader_flag = 2;
}

void			process_input(GLFWwindow *window, float camera_pos[3], \
	t_render_config *config, float delta_time)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	polymode(window, GLFW_KEY_COMMA, &(config->wireframe), &(config->w_flag));
	select_shader(window, config);
	if (config->w_flag == 1 && glfwGetKey(window, GLFW_KEY_COMMA) != GLFW_PRESS)
		config->w_flag = 0;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera_pos[0] -= 2.5 * delta_time;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera_pos[0] += 2.5 * delta_time;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera_pos[1] += 2.5 * delta_time;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera_pos[1] -= 2.5 * delta_time;
	if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		camera_pos[2] += 2.5 * delta_time;
	if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
		camera_pos[2] -= 2.5 * delta_time;
}
