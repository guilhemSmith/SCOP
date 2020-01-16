/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:03:30 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/16 11:17:22 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	mat4_mult(const float left[16], float right[16])
{
	float	tmp[16];
	int		i;
	int		j;
	int		k;

	ft_memcpy((void *)tmp, (const void *)right, sizeof(float) * 16);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			right[i * 4 + j] = 0;
			k = -1;
			while (++k < 4)
				right[i * 4 + j] += left[i * 4 + k] * tmp[k * 4 + j];
		}
	}
}
