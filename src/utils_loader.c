/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:32:12 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/19 18:20:06 by gsmith           ###   ########.fr       */
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

static int	add_face(int *val, t_list **dest, int size)
{
	t_list	*new_face;

	if (!(new_face = ft_lstnew(val, sizeof(int) * size)))
		return (-1);
	if (*dest != 0)
		ft_lstaddend(dest, new_face);
	else
		*dest = new_face;
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
		i = add_face(val, &(obj->triangles), 3);
	else if (i == 4)
		i = add_face(val, &(obj->quads), 4);
	else
		return (-1);
	return (i);
}

void		del_vertice_face(void *content, size_t size)
{
	ft_bzero((void *)content, size);
	ft_memdel(&content);
}

void		buffer_quad(t_parsed_obj *parsed, t_buffer_obj *buf, int i)
{
	int			j;
	t_list		*tmp;

	j = 0;
	tmp = parsed->quads;
	while (tmp)
	{
		buf->indices[i * 3 + j * 6] = ((int *)tmp->content)[0] - 1;
		buf->indices[i * 3 + j * 6 + 1] = ((int *)tmp->content)[1] - 1;
		buf->indices[i * 3 + j * 6 + 2] = ((int *)tmp->content)[2] - 1;
		buf->indices[i * 3 + j * 6 + 3] = ((int *)tmp->content)[2] - 1;
		buf->indices[i * 3 + j * 6 + 4] = ((int *)tmp->content)[3] - 1;
		buf->indices[i * 3 + j * 6 + 5] = ((int *)tmp->content)[0] - 1;
		tmp = tmp->next;
		j++;
	}
}
