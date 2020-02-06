/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:16:52 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/06 14:09:51 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_adv.h"
#include <math.h>

void	vec3_normalize(const float vec[3], float norm[3])
{
	float	len;

	len = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	norm[0] = vec[0] / len;
	norm[1] = vec[1] / len;
	norm[2] = vec[2] / len;
}

void	vec4_apply_mat4(const float mat[16], float vec[4])
{
	float	tmp[4];
	int		i;
	int		k;

	ft_memcpy((void *)tmp, (const void *)vec, sizeof(float) * 4);
	i = -1;
	while (++i < 4)
	{
		vec[i] = 0;
		k = -1;
		while (++k < 4)
			vec[i] += mat[i * 4 + k] * tmp[k];
	}
}
