/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:32:50 by gsmith            #+#    #+#             */
/*   Updated: 2018/03/28 11:20:52 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_bytes;
	unsigned char	byte;

	s_bytes = (unsigned char *)s;
	byte = (unsigned char)c;
	i = -1;
	while (++i < n)
		if (s_bytes[i] == byte)
			return ((void *)s + i);
	return (NULL);
}
