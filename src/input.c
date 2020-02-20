/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:40:51 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/20 14:58:14 by gsmith           ###   ########.fr       */
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

static void		update_shader(GLFWwindow *window, t_render_config *conf)
{
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && conf->alpha_flag == 0)
	{
		conf->alpha_flag = 1;
		conf->target_alpha = (int)(conf->target_alpha + 1) % 2;
	}
	else if (conf->alpha_flag && glfwGetKey(window, GLFW_KEY_T) != GLFW_PRESS)
		conf->alpha_flag = 0;
	if (conf->target_alpha > conf->current_alpha)
		conf->current_alpha += TRANS_SPEED;
	else if (conf->target_alpha < conf->current_alpha)
		conf->current_alpha -= TRANS_SPEED;
}

void			process_input(GLFWwindow *window, float camera_pos[3], \
	t_render_config *config, float delta_time)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	polymode(window, GLFW_KEY_COMMA, &(config->wireframe), &(config->w_flag));
	update_shader(window, config);
	if (config->w_flag == 1 && glfwGetKey(window, GLFW_KEY_COMMA) != GLFW_PRESS)
		config->w_flag = 0;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera_pos[0] -= MOVE_SPEED * delta_time;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera_pos[0] += MOVE_SPEED * delta_time;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera_pos[1] += MOVE_SPEED * delta_time;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera_pos[1] -= MOVE_SPEED * delta_time;
	if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		camera_pos[2] += MOVE_SPEED * delta_time;
	if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
		camera_pos[2] -= MOVE_SPEED * delta_time;
}
