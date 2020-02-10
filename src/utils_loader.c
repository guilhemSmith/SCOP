/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:32:12 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/10 18:06:00 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "loader.h"

int			parse_vertice(char *vertice, t_parsed_obj *obj)
{
	char	**words;
	int		i;
	float	val[3];
	t_list	*new_vertice;

	if (!(words = ft_strsplit_fun(vertice, &ft_isspace)))
		return (-1);
	i = -1;
	while (words[(++i) + 1])
	{
		if (i < 3)
			sscanf(words[i + 1], "%f", val + i);
		ft_memdel((void *)&(words[i + 1]));
	}
	if (ft_strcmp(words[0], "v") || i != 3)
		i = 0;
	ft_memdel((void *)&(words[0]));
	ft_memdel((void *)&words);
	if (!i || !(new_vertice = ft_lstnew(val, sizeof(int) * 3)))
		return (-1);
	if (obj->vertices != 0)
		ft_lstaddend(&(obj->vertices), new_vertice);
	else
		obj->vertices = new_vertice;
	return (0);
}

static int	add_triangle(int *val, t_parsed_obj *obj)
{
	t_list	*new_face;

	if (!(new_face = ft_lstnew(val, sizeof(int) * 3)))
		return (-1);
	if (obj->triangles != 0)
		ft_lstaddend(&(obj->triangles), new_face);
	else
		obj->triangles = new_face;
	return (0);
}

static int	add_quad(int *val, t_parsed_obj *obj)
{
	t_list	*new_face;

	if (!(new_face = ft_lstnew(val, sizeof(int) * 4)))
		return (-1);
	if (obj->quads != 0)
		ft_lstaddend(&(obj->quads), new_face);
	else
		obj->quads = new_face;
	return (0);
}

int			parse_face(char *face, t_parsed_obj *obj)
{
	char	**words;
	int		i;
	int		val[4];

	ft_bzero((void *)val, sizeof(int) * 4);
	if (!(words = ft_strsplit_fun(face, &ft_isspace)))
		return (-1);
	i = -1;
	while (words[(++i) + 1])
	{
		if (i < 4)
			sscanf(words[i + 1], "%d", val + i);
		ft_memdel((void *)&(words[i + 1]));
	}
	if (ft_strcmp(words[0], "f"))
		i = -1;
	ft_memdel((void *)&(words[0]));
	ft_memdel((void *)&words);
	if (i == 3)
		i = add_triangle(val, obj);
	else if (i == 4)
		i = add_quad(val, obj);
	else
		return (-1);
	return (i);
}

void		del_vertice_face(void *content, size_t size)
{
	ft_bzero((void *)content, size);
	ft_memdel(&content);
}
