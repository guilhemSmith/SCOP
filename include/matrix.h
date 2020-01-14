/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:10:11 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/14 19:04:26 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

void		mat4_set_diagonal(float mat[16], const float coef);
void		mat4_translate(const float mat[16], const float vec[3], \
	float res[16]);
void		mat4_rotate(const float mat[16], const float degr, \
	const float vec[3], float res[16]);
void		mat4_scale(const float mat[16], const float coef[3], \
	float res[16]);

#endif
