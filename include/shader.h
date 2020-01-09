/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:23:06 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/09 17:07:37 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# define VERTEX_SHADER_FILE "ressources/shaders/vertex.glsl"
# define FRAGMENT_SHADER_FILE "ressources/shaders/fragment.glsl"

# ifndef DEP
#  include <GL/glew.h>
# endif

static unsigned int	compile_shader(unsigned int *shader_ref, const char *src, \
	unsigned int shader_kind);
static unsigned int	link_shader(unsigned int *program_ref, \
	unsigned int shader_vertex, unsigned int shader_fragment);

#endif
