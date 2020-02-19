/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:51:22 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/19 09:31:40 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADER_H
# define LOADER_H

# ifndef DEP
#  include <GL/glew.h>
# endif

# include <fcntl.h>
# include <unistd.h>
# include "libft_adv.h"

typedef struct		s_parsed_obj
{
	t_list		*vertices;
	t_list		*triangles;
	t_list		*quads;
}					t_parsed_obj;

typedef struct		s_buffer_obj
{
	float		*vertices;
	int			nb_vertices;
	int			*triangles;
	int			nb_triangles;
	int			*quads;
	int			nb_quads;
}					t_buffer_obj;

int					parse_vertice(char *vertice, t_parsed_obj *obj);
int					parse_face(char *face, t_parsed_obj *obj);
void				del_vertice_face(void *content, size_t size);

#endif
