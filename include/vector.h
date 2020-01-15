/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:27:02 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/15 15:37:49 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

void	vec3_normalize(const float vec[3], float norm[3]);
void	vec4_apply_mat4(const float mat[16], float vec[4]);

#endif
