/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:18:06 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/10 17:45:34 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "utils_file.h"
#include "libft.h"

unsigned int	load_texture(unsigned int *texture, const char *filepath)
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
	ft_putendl("hello there");
	ft_memdel((void *)&file_content);
	return (0);
	if (get_format(file_content, &read_head, &raw_format))
	{
		ft_memdel((void *)file_content);
		return (-1);
	}
}

static unsigned int		get_format(const char *data, unsigned int *read_head, \
	int *flag)
{
	unsigned int	bound[2];
	unsigned int	i;
	int				next_bound;
	char			c;

	(void)flag;
	(void)read_head;
	next_bound = 0;
	bound[0] = 0;
	bound[1] = 0;
	i = 0;
	c = data[i];
	while (next_bound != 2 && c)
	{
		while (c && ft_isspace(c))
			c = data[++i];
		while (next_bound != 2 && c && c != '\n')
		{
			if (c != '#')
				bound[next_bound++] = i;
			else
			{
				if (next_bound == 1)
					bound[next_bound++] = i - 1;
				i = next_line(data + i);
			}
			c = data[++i];
		}
		while (c && ft_isspace(c))
			c = data[++i];
	}
	return (next_bound != 2 ? -1 : 0);
}
