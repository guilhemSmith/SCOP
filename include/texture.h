/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:19:22 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/13 11:46:35 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# ifndef DEP
#  include <GL/glew.h>
# endif

# define TEXTURE_FLAG_FORMAT_ASCII "P3"
# define TEXTURE_FLAG_FORMAT_RAW "P6"

static unsigned int		parse_ppm(const char *filepath, unsigned char **data, \
	int *width, int *height);
static unsigned int		get_format(const char *data, unsigned int *read_head, \
	int *flag);

#endif
