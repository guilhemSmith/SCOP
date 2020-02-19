/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:51:02 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/19 13:36:07 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

#include <stdlib.h>

static int		open_object(int argc, char *argv[])
{
	int		fd;

	if (argc != 2)
	{
		ft_putstr_fd("usage: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putendl_fd(" obj_filename", 2);
		ft_putendl_fd("\tobj_filename: file name of the 3d model to show.", 2);
		return (-1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_putendl_fd("ERROR::LOADER::FILENAME::OPEN_FAILED", 2);
		return (-1);
	}
	return (fd);
}

static int		parse_obj(int fd, t_parsed_obj *obj)
{
	char	*line;
	int		ret_val;

	while ((ret_val = get_next_line(fd, &line)) > 0)
	{
		if (line[0] && line[0] == 'v')
			ret_val = parse_vertice(line, obj);
		else if (line[0] && line[0] == 'f')
			ret_val = parse_face(line, obj);
		ft_strdel(&line);
		if (ret_val < 0)
		{
			ft_putendl_fd("ERROR::LOADER::LINE_INVALID", 2);
			break ;
		}
	}
	close(fd);
	if (ret_val)
	{
		ft_lstdel(&(obj->quads), &del_vertice_face);
		ft_lstdel(&(obj->triangles), &del_vertice_face);
		ft_lstdel(&(obj->vertices), &del_vertice_face);
		ft_putendl_fd("ERROR::LOADER::PARSING_FAILED", 2);
	}
	return (ret_val);
}

static int		buff_vertice(t_list **lst, float **vert)
{
	int			len;
	int			i;
	int			j;
	t_list		*tmp;

	i = 0;
	len = ft_lstlen(*lst);
	if (!((*vert) = (float *)malloc(sizeof(float) * 3 * len)))
	{
		ft_lstdel(lst, del_vertice_face);
		return (-1);
	}
	while (*lst)
	{
		j = -1;
		while (++j < 3)
			(*vert)[i * 3 + j] = ((float *)(*lst)->content)[j];
		tmp = (*lst)->next;
		ft_lstdelone(lst, &del_vertice_face);
		*lst = tmp;
		i++;
	}
	return (0);
}

static int		buff_face(t_list **lst, int **face, int size)
{
	int			len;
	int			i;
	int			j;
	t_list		*tmp;

	i = 0;
	len = ft_lstlen(*lst);
	if (!((*face) = (int *)malloc(sizeof(int) * size * len)))
	{
		ft_lstdel(lst, del_vertice_face);
		return (-1);
	}
	while (*lst)
	{
		j = -1;
		while (++j < size)
			(*face)[i * size + j] = ((int *)(*lst)->content)[j] - 1;
		tmp = (*lst)->next;
		ft_lstdelone(lst, &del_vertice_face);
		*lst = tmp;
		i++;
	}
	return (0);
}

unsigned int	load_object(int argc, char *argv[])
{
	int				fd;
	unsigned int	vao;
	unsigned int	vbo;
	unsigned int	ebo[2];
	int				err_val;
	t_parsed_obj	parsed_data;
	t_buffer_obj	buffer_data;

	if ((fd = open_object(argc, argv)) < 0)
		return (0);
	ft_bzero((void *)&parsed_data, sizeof(t_parsed_obj));
	if (parse_obj(fd, &parsed_data))
		return (0);
	ft_bzero((void *)&buffer_data, sizeof(t_buffer_obj));
	buffer_data.nb_vertices = ft_lstlen(parsed_data.vertices) * 3;
	err_val = buff_vertice(&(parsed_data.vertices), &(buffer_data.vertices));
	buffer_data.nb_triangles = ft_lstlen(parsed_data.triangles) * 3;
	err_val = buff_face(&(parsed_data.triangles), &(buffer_data.triangles), 3);
	buffer_data.nb_quads = ft_lstlen(parsed_data.quads) * 4;
	err_val = buff_face(&(parsed_data.quads), &(buffer_data.quads), 4);
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(2, ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, buffer_data.nb_vertices * sizeof(float), buffer_data.vertices, GL_STATIC_DRAW);
	if (buffer_data.nb_triangles > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_data.nb_triangles * sizeof(int), buffer_data.triangles, GL_STATIC_DRAW);
	}
	if (buffer_data.nb_quads > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_data.nb_quads * sizeof(int), buffer_data.quads, GL_STATIC_DRAW);
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	ft_memdel((void **)&(buffer_data.vertices));
	ft_memdel((void **)&(buffer_data.triangles));
	ft_memdel((void **)&(buffer_data.quads));
	return (vao);
}
