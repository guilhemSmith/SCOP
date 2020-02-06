/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:04:54 by gsmith            #+#    #+#             */
/*   Updated: 2018/03/28 11:30:00 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*b_bytes;
	unsigned char	byte;

	b_bytes = (unsigned char *)b;
	byte = (unsigned char)c;
	i = -1;
	while (++i < len)
		b_bytes[i] = byte;
	return (b);
}
