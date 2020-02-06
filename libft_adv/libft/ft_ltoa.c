/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:38:37 by gsmith            #+#    #+#             */
/*   Updated: 2018/05/11 18:26:29 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdlib.h>

#include <stdio.h>

static t_bool	init_ltoa(long n, char **res)
{
	t_bool			neg;
	int				len;
	long			div;

	len = 1;
	neg = 0;
	if (n < 0 && len++)
		neg = 1;
	div = 10;
	while (n / div != 0 && div < (LONG_MAX / 10))
	{
		div = div * 10;
		len++;
	}
	if (n / div != 0)
		len++;
	if (!(*res = (char *)malloc(sizeof(char) * (len + 1))))
		return (-1);
	return (neg);
}

char			*ft_ltoa(long n)
{
	int				neg;
	char			*res;
	int				i;
	long			div;

	if ((neg = init_ltoa(n, &res)) == -1)
		return (NULL);
	i = 0;
	if (neg)
		res[i++] = '-';
	div = 10;
	while (n / div != 0 && div < (LONG_MAX / 10))
		div = div * 10;
	if (n / div == 0)
		div = div / 10;
	while (div > 0)
	{
		res[i++] = (-2 * neg + 1) * (n / div) + '0';
		n = (n % div);
		div = div / 10;
	}
	res[i] = 0;
	return (res);
}
