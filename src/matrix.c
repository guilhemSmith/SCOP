/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:11:03 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/14 19:04:14 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

static void	mat4_mult(const float lt[16], const float rt[16], float res[16])
{
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			res[i * 4 + j] = 0;
			k = -1;
			while (++k < 4)
				res[i * 4 + j] += lt[i * 4 + k] * rt[k * 4 + j];
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

void		mat4_translate(const float mat[16], const float vec[3], \
	float res[16])
{
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			res[i * 4 + j] = mat[i * 4 + j];
		if (j == 3)
			res[i * 4 + j] += vec[i];
	}
}

void		mat4_rotate(const float mat[16], const float degr, \
	const float vec[3], float res[16])
{
	float	normed[3];
	float	pivot[16];
	float	c;
	float	s;
	float	nc;

	vec3_normalize(vec, normed);
	c = cos(degr * M_PI / 180);
	s = sin(degr * M_PI / 180);
	nc = 1 - c;
	ft_bzero((void *)pivot, sizeof(float) * 16);
	pivot[0] = c + normed[0] * normed[0] * nc;
	pivot[1] = normed[0] * normed[1] * nc - normed[2] * s;
	pivot[2] = normed[0] * normed[2] * nc + normed[1] * s;
	pivot[4] = normed[0] * normed[1] * nc + normed[2] * s;
	pivot[5] = c + normed[1] * normed[1] * nc;
	pivot[6] = normed[1] * normed[2] * nc - normed[0] * s;
	pivot[8] = normed[0] * normed[2] * nc - normed[1] * s;
	pivot[9] = normed[1] * normed[2] * nc + normed[0] * s;
	pivot[10] = c + normed[2] * normed[2] * nc;
	pivot[15] = 1;
	mat4_mult(pivot, mat, res);
}

void		mat4_scale(const float mat[16], const float coef[3], \
	float res[16])
{
	float scale[16];

	mat4_set_diagonal(scale, 1);
	scale[0] = coef[0];
	scale[5] = coef[1];
	scale[10] = coef[2];
	mat4_mult(scale, mat, res);
}
