/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:41:42 by gsmith            #+#    #+#             */
/*   Updated: 2018/03/28 11:33:07 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	casted_c;

	i = -1;
	casted_c = (char)c;
	while (s[++i])
		if (s[i] == casted_c)
			return ((char *)s + i);
	if (s[i] == casted_c)
		return ((char *)s + i);
	return (NULL);
}
