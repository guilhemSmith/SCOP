/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:01:26 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/13 13:07:57 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFF_SIZE 2048

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

static unsigned int	fuse_read(unsigned int fd, char **txt, char *buf)
{
	int			read_flag;
	char		*new_ptr;

	while ((read_flag = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[read_flag] = 0;
		if (!(new_ptr = ft_strjoin(*txt, buf)))
		{
			ft_putendl_fd("ERROR::FILE::MALLOC_FAILED", 2);
			ft_strdel(txt);
			return (-1);
		}
		ft_strdel(txt);
		*txt = new_ptr;
	}
	ft_bzero((void *)buf, BUFF_SIZE);
	close(fd);
	if (read_flag < 0)
	{
		ft_putendl_fd("ERROR::FILE::READING_FAILED", 2);
		ft_strdel(txt);
		new_ptr = NULL;
		return (-1);
	}
	return (0);
}

unsigned int		read_file(const char **output, const char *filename)
{
	unsigned int	fd;
	char			buf[BUFF_SIZE + 1];
	char			*file_txt;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_putstr_fd("ERROR::FILE::OPEN_FAILED\nFILE:", 2);
		ft_putendl_fd(filename, 2);
		return (-1);
	}
	if (!(file_txt = ft_strdup("")))
	{
		close(fd);
		ft_putendl_fd("ERROR::FILE::MALLOC_FAILED", 2);
		return (-1);
	}
	if (fuse_read(fd, &file_txt, buf))
		return (-1);
	*output = file_txt;
	return (0);
}

unsigned int		next_line(const char *data)
{
	unsigned int	i;
	char			c;

	i = 0;
	c = data[i];
	while (c && c != '\n')
		c = data[++i];
	return (c == 0 ? i : i + 1);
}

char				*get_word(const char *data, unsigned int *read_head)
{
	unsigned int	i;
	char			c;
	unsigned int	bound[2];

	i = *read_head;
	c = data[i];
	while (c && ft_isspace(c))
		c = data[++i];
	if (c == 0)
		return (NULL);
	if (c == '#')
	{
		i += next_line(data + i);
		*read_head = i;
		return (get_word(data, read_head));
	}
	bound[0] = i;
	while (c && !ft_isspace(c))
		c = data[++i];
	bound[1] = i;
	while (c && ft_isspace(c))
		c = data[++i];
	*read_head = i;
	return (ft_strsub(data, bound[0], bound[1] - bound[0]));
}
