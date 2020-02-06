/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:14:13 by gsmith            #+#    #+#             */
/*   Updated: 2018/03/28 11:25:17 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst_bytes;
	unsigned char	*src_bytes;

	dst_bytes = (unsigned char *)dst;
	src_bytes = (unsigned char *)src;
	if (dst_bytes < src_bytes)
	{
		i = -1;
		while (++i < len)
			dst_bytes[i] = src_bytes[i];
	}
	else
	{
		i = len;
		while (i-- > 0)
			dst_bytes[i] = src_bytes[i];
	}
	return (dst);
}
