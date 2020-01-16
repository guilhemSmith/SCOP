/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:20:21 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/16 15:35:06 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "renderer.h"
#include <math.h>

static void	camera_matrix(float view[16], const float camera_pos[3])
{
	mat4_set_diagonal(view, 1);
	mat4_translate(view, camera_pos);
}

void		render_object(t_render_config config, t_obj_render object, \
	const float camera_pos[3])
{
	float			model[16];
	float			view[16];
	float			projection[16];

	mat4_set_diagonal(model, 1);
	mat4_rotate(model, (float)glfwGetTime(), (const float[3]){0.5, 1, 0});
	camera_matrix(view, camera_pos);
	mat4_perspective(config.fov, config.width / config.height, \
		(const float[2]){0.1, 100}, projection);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, object.texture);
	glUseProgram(config.shader);
	glUniformMatrix4fv(glGetUniformLocation(config.shader, "model"), 1, \
		GL_FALSE, model);
	glUniformMatrix4fv(glGetUniformLocation(config.shader, "view"), 1, \
		GL_FALSE, view);
	glUniformMatrix4fv(glGetUniformLocation(config.shader, "projection"), 1, \
		GL_FALSE, projection);
	glBindVertexArray(object.vao);
	glDrawArrays(object.mode, object.start, object.count);
	glBindVertexArray(0);
}
