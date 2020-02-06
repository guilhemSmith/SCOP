/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:11:03 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/06 14:10:21 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_adv.h"
#include "utils_matrix.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

void		mat4_set_diagonal(float mat[16], const float coef)
{
	ft_bzero((void *)mat, sizeof(float) * 16);
	mat[0] = coef;
	mat[5] = coef;
	mat[10] = coef;
	mat[15] = coef;
}

void		mat4_perspective(float rad, float ratio, const float z_range[2], \
	float persp[16])
{
	float	tan_half;

	ft_bzero((void *)persp, sizeof(float) * 16);
	tan_half = tan(rad / 2);
	persp[0] = 1 / (ratio * tan_half);
	persp[5] = 1 / tan_half;
	persp[10] = -(z_range[1] + z_range[0]) / (z_range[1] - z_range[0]);
	persp[11] = -1;
	persp[14] = -(2 * z_range[1] * z_range[0]) / (z_range[1] - z_range[0]);
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
