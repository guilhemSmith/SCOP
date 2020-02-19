/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_loader_gl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:04:54 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/19 18:16:41 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

void		gl_load(t_obj_render *obj, t_buffer_obj *buffer)
{
	glGenVertexArrays(1, &(obj->vao));
	glGenBuffers(1, &(obj->vbo));
	glGenBuffers(2, &(obj->ebo));
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
