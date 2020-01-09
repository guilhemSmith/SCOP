/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:01:26 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/09 18:09:56 by gsmith           ###   ########.fr       */
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
			ft_putendl_fd("malloc error", 2);
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
		ft_putendl_fd("Error while reading a file.", 2);
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
		ft_putstr_fd("Can't open file: ", 2);
		ft_putendl_fd(filename, 2);
		return (-1);
	}
	if (!(file_txt = ft_strdup("")))
	{
		close(fd);
		ft_putendl_fd("malloc error", 2);
		return (-1);
	}
	if (fuse_read(fd, &file_txt, buf))
		return (-1);
	*output = file_txt;
	return (0);
}
