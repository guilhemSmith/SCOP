/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:10:11 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/15 14:52:20 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

void		mat4_set_diagonal(float mat[16], const float coef);
void		mat4_translate(float mat[16], const float vec[3]);
void		mat4_rotate(float mat[16], float rad, const float vec[3]);
void		mat4_scale(float mat[16], const float coef[3]);

#endif
