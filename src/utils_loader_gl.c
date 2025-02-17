/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_loader_gl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:04:54 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/21 15:48:57 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

int			allocate_buffer(int len, unsigned int size, void **ptr)
{
	if (len == 0)
	{
		ft_putendl_fd("ERROR::BUFFER::EMPTY", 2);
		return (-1);
	}
	if (!(*ptr = ft_memalloc(len * size)))
	{
		ft_putendl_fd("ERROR::BUFFER::MALLOC_FAILED", 2);
		return (-1);
	}
	return (0);
}

static void	update_vertices(float *vert_ptr, float max[3], float min[3])
{
	vert_ptr[0] -= min[0] + (max[0] - min[0]) / 2;
	vert_ptr[1] -= min[1] + (max[1] - min[1]) / 2;
	vert_ptr[2] -= min[2] + (max[2] - min[2]) / 2;
	vert_ptr[3] = (vert_ptr[2] - min[2]) / (max[2] - min[2]);
	vert_ptr[4] = (vert_ptr[1] - min[1]) / (max[1] - min[1]);
}

static void	update_cam(float *cam_z, float max[3], float min[3])
{
	float		range[3];
	float		max_range;

	range[0] = max[0] - min[0];
	range[1] = max[1] - min[1];
	range[2] = max[2] - min[2];
	max_range = range[0];
	if (max_range < range[1])
		max_range = range[1];
	if (max_range < range[2])
		max_range = range[2];
	*cam_z = -max_range * 1.5;
}

void		repos_model(t_buffer_obj *buffer, float *cam_z)
{
	float		max[3];
	float		min[3];
	int			i;
	int			j;

	ft_bzero((void *)max, sizeof(int) * 3);
	ft_bzero((void *)min, sizeof(int) * 3);
	i = -1;
	while (++i < buffer->nb_vert / 5)
	{
		j = -1;
		while (++j < 3)
		{
			if (buffer->vertices[i * 5 + j] > max[j])
				max[j] = buffer->vertices[i * 5 + j];
			else if (buffer->vertices[i * 5 + j] < min[j])
				min[j] = buffer->vertices[i * 5 + j];
		}
	}
	while (--i >= 0)
		update_vertices(buffer->vertices + i * 5, max, min);
	update_cam(cam_z, max, min);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), \
		(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), \
		(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
