/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:26:14 by gsmith            #+#    #+#             */
/*   Updated: 2018/03/28 11:15:42 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst_bytes;
	unsigned char	*src_bytes;

	dst_bytes = (unsigned char *)dst;
	src_bytes = (unsigned char *)src;
	i = -1;
	while (++i < n)
		dst_bytes[i] = src_bytes[i];
	return (dst);
}
