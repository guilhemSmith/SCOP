/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_fun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 12:07:33 by gsmith            #+#    #+#             */
/*   Updated: 2018/03/30 12:12:20 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

static size_t	nb_str(char const *s, int (*isseparator)(char))
{
	size_t	nb;
	size_t	i;

	nb = 0;
	i = 0;
	while (s[i])
	{
		while (isseparator(s[i]))
			i++;
		nb += s[i] != 0;
		while (s[i] && !isseparator(s[i]))
			i++;
	}
	return (nb);
}

static size_t	extract_str(char **dst, const char *src,
		int (*isseparator)(char))
{
	size_t	len;
	size_t	i;

	len = 0;
	while (src[len] && !isseparator(src[len]))
		len++;
	if (!(*dst = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (i < len)
	{
		(*dst)[i] = src[i];
		i++;
	}
	(*dst)[i] = 0;
	return (i);
}

char			**ft_strsplit_fun(char const *s, int (*isseparator)(char))
{
	char	**res;
	size_t	i;
	size_t	nb;
	size_t	nb_s;

	if (!s)
		return (NULL);
	nb_s = nb_str(s, isseparator);
	if (!(res = (char **)malloc(sizeof(char *) * (nb_s + 1))))
		return (NULL);
	res[nb_s] = 0;
	i = 0;
	nb = 0;
	while (nb < nb_s)
	{
		while (isseparator(s[i]))
			i++;
		i += extract_str(res + nb, s + i, isseparator);
		nb++;
	}
	return (res);
}
