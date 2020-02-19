/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:51:22 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/19 18:21:39 by gsmith           ###   ########.fr       */
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
# include "renderer.h"

typedef struct		s_parsed_obj
{
	t_list		*vertices;
	t_list		*triangles;
	t_list		*quads;
}					t_parsed_obj;

typedef struct		s_buffer_obj
{
	float		*vertices;
	int			nb_vert;
	int			*indices;
	int			nb_indices;
}					t_buffer_obj;

void				gl_load(t_obj_render *obj, t_buffer_obj *buffer);

int					parse_vertice(char *vertice, t_parsed_obj *obj);
int					parse_face(char *face, t_parsed_obj *obj);
void				del_vertice_face(void *content, size_t size);
void				buffer_quad(t_parsed_obj *parsed, t_buffer_obj *buf, int i);

#endif
