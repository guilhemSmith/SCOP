/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:44:02 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/09 14:45:30 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# define GL_SILENCE_DEPRECATION
# define WIDTH_DEF 800
# define HEIGHT_DEF 600

# ifndef DEP
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
# endif

# include "libft.h"

unsigned int		load_shader(void);

#endif
