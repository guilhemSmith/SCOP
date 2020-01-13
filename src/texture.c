/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:18:06 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/13 17:30:13 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "utils_file.h"
#include "libft.h"
#include <stdlib.h>

unsigned int			load_texture(unsigned int *texture, \
	const char *filepath)
{
	int				width;
	int				height;
	unsigned char	*data;

	if (parse_ppm(filepath, &data, &width, &height))
	{
		ft_putstr_fd("ERROR::TEXTURE::LOAD_FAILED\nFILE: ", 2);
		ft_putendl_fd(filepath, 2);
		return (-1);
	}
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, \
		GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	ft_memdel((void **)&data);
	return (0);
}

static unsigned int		parse_ppm(const char *filepath, unsigned char **data, \
	int *width, int *height)
{
	const char		*fc;
	int				is_raw;
	unsigned int	rd_head;
	int				range;
	int				ret_val;

	ret_val = 0;
	if (read_file(&fc, filepath))
		return (-1);
	rd_head = 0;
	if (get_format(fc, &rd_head, &is_raw) || get_int(fc, &rd_head, width) \
		|| get_int(fc, &rd_head, height) || get_int(fc, &rd_head, &range))
		ret_val = -1;
	else if (is_raw || range > 255 || range < 1)
	{
		ft_putendl_fd("ERROR::TEXTURE::UNSUPPORTED_FORMAT", 2);
		ret_val = -1;
	}
	else if (!(*data = get_values(fc, &rd_head, *width, *height)))
		ret_val = -1;
	ft_memdel((void **)&fc);
	return (ret_val);
}

static unsigned int		get_format(const char *data, unsigned int *rd_head, \
	int *flag)
{
	char	*word;

	if (!(word = get_word(data, rd_head)))
		return (-1);
	if (!ft_strcmp(word, TEXTURE_FLAG_FORMAT_ASCII))
		*flag = 0;
	else if (!ft_strcmp(word, TEXTURE_FLAG_FORMAT_RAW))
		*flag = 1;
	else
	{
		ft_putendl_fd("ERROR::TEXTURE::HEADER::FORMAT_UNKNOWN", 2);
		ft_memdel((void **)&word);
		return (-1);
	}
	ft_memdel((void **)&word);
	return (0);
}

static unsigned int		get_int(const char *data, unsigned int *rd_head, \
	int *value)
{
	char	*word;
	int		atoi;

	if (!(word = get_word(data, rd_head)))
		return (-1);
	atoi = ft_atoi(word);
	ft_memdel((void **)&word);
	if (!atoi)
	{
		ft_putendl_fd("ERROR::TEXTURE::HEADER::VALUE_NAN_OR_NULL", 2);
		return (-1);
	}
	*value = atoi;
	return (0);
}

static unsigned char	*get_values(const char *data, unsigned int *rd_head, \
	unsigned int w, unsigned h)
{
	char			*word;
	unsigned int	x;
	unsigned int	y;
	unsigned char	value;
	unsigned char	*ptr;

	if (!(ptr = (unsigned char *)malloc(sizeof(unsigned char) * 3 * w * h)))
	{
		ft_putendl_fd("ERROR::TEXTURE::MALLOC_FAILED", 2);
		return (NULL);
	}
	x = 0;
	y = h - 1;
	while ((word = get_word(data, rd_head)))
	{
		value = (unsigned char)ft_atoi(word);
		ft_memdel((void **)&word);
		ptr[y * w * 3 + x++] = value;
		if (x >= w * 3)
		{
			x = 0;
			y--;
		}
	}
	return (ptr);
}
