/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:18:06 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/13 12:45:24 by gsmith           ###   ########.fr       */
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

	(void)width;
	(void)height;
	(void)data;
	if (read_file(&file_content, filepath))
		return (-1);
	read_head = 0;
	if (get_format(file_content, &read_head, &raw_format))
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
		ft_memdel((void **)&word);
		return (-1);
	}
	ft_memdel((void **)&word);
	return (0);
}
