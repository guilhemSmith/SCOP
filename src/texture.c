/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:18:06 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/13 13:09:47 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "utils_file.h"
#include "libft.h"

unsigned int			load_texture(unsigned int *texture, \
	const char *filepath)
{
	int				width;
	int				height;
	unsigned char	*data;

	if (parse_ppm(filepath, &data, &width, &height))
	{
		ft_putstr_fd("Failed to load texture from file: ", 2);
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
	return (0);
}

static unsigned int		parse_ppm(const char *filepath, unsigned char **data, \
	int *width, int *height)
{
	const char		*file_content;
	int				raw_format;
	unsigned int	read_head;
	int				color_range;

	(void)data;
	if (read_file(&file_content, filepath))
		return (-1);
	read_head = 0;
	if (get_format(file_content, &read_head, &raw_format) \
		|| get_int(file_content, &read_head, width) \
		|| get_int(file_content, &read_head, height) \
		|| get_int(file_content, &read_head, &color_range))
	{
		ft_memdel((void **)&file_content);
		return (-1);
	}
	if (raw_format)
		ft_putendl("raw file");
	else
		ft_putendl("ascii file");
	ft_memdel((void **)&file_content);
	return (0);
}

static unsigned int		get_format(const char *data, unsigned int *read_head, \
	int *flag)
{
	char	*word;

	if (!(word = get_word(data, read_head)))
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

static unsigned int		get_int(const char *data, unsigned int *read_head, \
	int *value)
{
	char	*word;
	int		atoi;

	if (!(word = get_word(data, read_head)))
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
