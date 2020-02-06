/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:35:52 by gsmith            #+#    #+#             */
/*   Updated: 2018/03/28 11:28:21 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst_bytes;
	unsigned char	*src_bytes;
	unsigned char	byte;

	byte = (unsigned char)c;
	dst_bytes = (unsigned char *)dst;
	src_bytes = (unsigned char *)src;
	i = -1;
	while (++i < n)
	{
		dst_bytes[i] = src_bytes[i];
		if (src_bytes[i] == byte)
			return (dst + i + 1);
	}
	return (NULL);
}
