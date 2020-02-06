/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:32:50 by gsmith            #+#    #+#             */
/*   Updated: 2018/04/10 17:47:09 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int				ft_atoi_base(const char *str, const char *base)
{
	long	res;
	int		b_size;
	int		sign;
	int		i;
	int		digit;

	res = 0;
	b_size = ft_strlen(base);
	sign = (b_size != 10 || str[0] != '-') ? 1 : -1;
	i = (b_size != 10 || (str[0] != '-' && str[0] != '+')) ? -1 : 0;
	while (str[++i])
	{
		digit = 0;
		while (digit < b_size && base[digit] != str[i])
			digit++;
		if (digit == b_size)
			break ;
		res = res * b_size + digit;
	}
	return (sign * (int)res);
}
