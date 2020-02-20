/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_loader_gl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:04:54 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/20 13:11:05 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

void		repos_model(t_buffer_obj *buffer)
{
	float		max[3];
	float		min[3];
	int			i;
	int			j;

	ft_bzero((void *)max, sizeof(int) * 3);
	ft_bzero((void *)min, sizeof(int) * 3);
	i = -1;
	while (++i < buffer->nb_vert / 3)
	{
		j = -1;
		while (++j < 3)
		{
			if (buffer->vertices[i * 3 + j] > max[j])
				max[j] = buffer->vertices[i * 3 + j];
			else if (buffer->vertices[i * 3 + j] < min[j])
				min[j] = buffer->vertices[i * 3 + j];
		}
	}
	i = -1;
	while (++i < buffer->nb_vert / 3)
	{
		buffer->vertices[i * 3] -= min[0] + (max[0] - min[0]) / 2;
		buffer->vertices[i * 3 + 1] -= min[1] + (max[1] - min[1]) / 2;
		buffer->vertices[i * 3 + 2] -= min[2] + (max[2] - min[2]) / 2;
	}
}

void		gl_load(t_obj_render *obj, t_buffer_obj *buffer)
{
	glGenVertexArrays(1, &(obj->vao));
	glGenBuffers(1, &(obj->vbo));
	glGenBuffers(1, &(obj->ebo));
	glBindVertexArray(obj->vao);
	glBindBuffer(GL_ARRAY_BUFFER, obj->vbo);
	glBufferData(GL_ARRAY_BUFFER, buffer->nb_vert * sizeof(float), \
		buffer->vertices, GL_STATIC_DRAW);
	if (buffer->nb_indices > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, \
			buffer->nb_indices * sizeof(int), buffer->indices, GL_STATIC_DRAW);
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), \
		(void*)0);
	glEnableVertexAttribArray(0);
}
