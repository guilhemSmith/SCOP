/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:16:38 by gsmith            #+#    #+#             */
/*   Updated: 2018/03/28 11:42:26 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*s_bytes;

	s_bytes = (unsigned char *)s;
	i = -1;
	while (++i < n)
		s_bytes[i] = 0;
}
