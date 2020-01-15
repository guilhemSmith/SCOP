/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:11:03 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/15 15:28:53 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

static void	mat4_mult(const float left[16], float right[16])
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

void		mat4_set_diagonal(float mat[16], const float coef)
{
	ft_bzero((void *)mat, sizeof(float) * 16);
	mat[0] = coef;
	mat[5] = coef;
	mat[10] = coef;
	mat[15] = coef;
}

void		mat4_translate(float mat[16], const float vec[3])
{
	float	translator[16];

	mat4_set_diagonal(translator, 1);
	translator[12] = vec[0];
	translator[13] = vec[1];
	translator[14] = vec[2];
	mat4_mult(translator, mat);
}

void		mat4_rotate(float mat[16], float rad, const float vec[3])
{
	float	normed[3];
	float	pivot[16];
	float	c;
	float	s;
	float	nc;

	vec3_normalize(vec, normed);
	c = cos(rad);
	s = sin(rad);
	nc = 1 - c;
	ft_bzero((void *)pivot, sizeof(float) * 16);
	pivot[0] = c + normed[0] * normed[0] * nc;
	pivot[1] = normed[0] * normed[1] * nc + normed[2] * s;
	pivot[2] = normed[0] * normed[2] * nc - normed[1] * s;
	pivot[4] = normed[0] * normed[1] * nc - normed[2] * s;
	pivot[5] = c + normed[1] * normed[1] * nc;
	pivot[6] = normed[1] * normed[2] * nc + normed[0] * s;
	pivot[8] = normed[0] * normed[2] * nc + normed[1] * s;
	pivot[9] = normed[1] * normed[2] * nc - normed[0] * s;
	pivot[10] = c + normed[2] * normed[2] * nc;
	pivot[15] = 1;
	mat4_mult(pivot, mat);
}

void		mat4_scale(float mat[16], const float coef[3])
{
	float scale[16];

	mat4_set_diagonal(scale, 1);
	scale[0] = coef[0];
	scale[5] = coef[1];
	scale[10] = coef[2];
	mat4_mult(scale, mat);
}
