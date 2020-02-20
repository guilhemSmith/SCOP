/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:51:02 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/20 15:48:21 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

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

static int		buff_vertice(t_list **lst, t_buffer_obj *buf)
{
	int			i;
	int			j;
	t_list		*tmp;

	buf->nb_vert = ft_lstlen(*lst) * 5;
	i = 0;
	if (!(buf->vertices = (float *)ft_memalloc(sizeof(float) * buf->nb_vert)))
	{
		ft_lstdel(lst, del_vertice_face);
		return (-1);
	}
	while (*lst)
	{
		j = -1;
		while (++j < 3)
			buf->vertices[i * 5 + j] = ((float *)(*lst)->content)[j];
		tmp = (*lst)->next;
		ft_lstdelone(lst, &del_vertice_face);
		*lst = tmp;
		i++;
	}
	return (0);
}

static int		buff_triangles(t_parsed_obj *parsed, t_buffer_obj *buf)
{
	int			i;
	t_list		*tmp;

	buf->nb_indices = ft_lstlen(parsed->triangles) * 3 \
		+ ft_lstlen(parsed->quads) * 6;
	if (!(buf->indices = (int *)ft_memalloc(sizeof(int) * buf->nb_indices)))
	{
		ft_lstdel(&(parsed->triangles), &del_vertice_face);
		ft_lstdel(&(parsed->quads), &del_vertice_face);
		return (-1);
	}
	i = 0;
	tmp = parsed->triangles;
	while (tmp)
	{
		buf->indices[i * 3] = ((int *)tmp->content)[0] - 1;
		buf->indices[i * 3 + 1] = ((int *)tmp->content)[1] - 1;
		buf->indices[i * 3 + 2] = ((int *)tmp->content)[2] - 1;
		tmp = tmp->next;
		i++;
	}
	buffer_quad(parsed, buf, i);
	ft_lstdel(&(parsed->triangles), &del_vertice_face);
	ft_lstdel(&(parsed->quads), &del_vertice_face);
	return (0);
}

unsigned int	load_object(t_obj_render *obj, int argc, char *argv[])
{
	int				fd;
	int				err_val;
	t_parsed_obj	parsed_data;
	t_buffer_obj	buffer_data;

	if ((fd = open_object(argc, argv)) < 0)
		return (-1);
	ft_bzero((void *)&parsed_data, sizeof(t_parsed_obj));
	if (parse_obj(fd, &parsed_data))
		return (-1);
	ft_bzero((void *)&buffer_data, sizeof(t_buffer_obj));
	err_val = buff_vertice(&(parsed_data.vertices), &buffer_data);
	err_val = buff_triangles(&parsed_data, &buffer_data);
	obj->nb_elem = buffer_data.nb_indices * 6;
	repos_model(&buffer_data);
	gl_load(obj, &buffer_data);
	ft_memdel((void **)&(buffer_data.vertices));
	ft_memdel((void **)&(buffer_data.indices));
	return (err_val);
}
