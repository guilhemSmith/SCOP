/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:22:21 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/06 14:10:10 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"
#include "libft_adv.h"
#include "utils_file.h"

void				shader_set_mat4(unsigned int shader, const char *field, \
	const float mat[16])
{
	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, field), 1, GL_FALSE, mat);
}

void				shader_set_vec3(unsigned int shader, const char *field, \
	const float vec[3])
{
	glUseProgram(shader);
	glUniform3fv(glGetUniformLocation(shader, field), 1, vec);
}

unsigned int		load_shader(unsigned int *shader_program, \
	const char *vertex_path, const char *fragment_path)
{
	const char				*src;
	unsigned int			shader_part[2];

	if (read_file(&src, vertex_path) \
		|| compile_shader(&(shader_part[0]), src, GL_VERTEX_SHADER))
	{
		ft_memdel((void *)&src);
		return (-1);
	}
	ft_memdel((void *)&src);
	if (read_file(&src, fragment_path) \
		|| compile_shader(&(shader_part[1]), src, GL_FRAGMENT_SHADER))
	{
		ft_memdel((void *)&src);
		glDeleteShader(shader_part[0]);
		return (-1);
	}
	ft_memdel((void *)&src);
	if (link_shader(shader_program, shader_part[0], shader_part[1]))
	{
		glDeleteShader(shader_part[0]);
		glDeleteShader(shader_part[0]);
		return (-1);
	}
	return (0);
}

static unsigned int	compile_shader(unsigned int *shader_ref, const char *src, \
	unsigned int shader_kind)
{
	unsigned int	shader_tmp;
	int				success;
	char			info_log[512];

	shader_tmp = glCreateShader(shader_kind);
	glShaderSource(shader_tmp, 1, &src, NULL);
	glCompileShader(shader_tmp);
	glGetShaderiv(shader_tmp, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader_tmp, 512, NULL, info_log);
		if (shader_kind == GL_VERTEX_SHADER)
			ft_putendl_fd("ERROR::SHADER::VERTEX::COMPILATION_FAILED", 2);
		else if (shader_kind == GL_FRAGMENT_SHADER)
			ft_putendl_fd("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED", 2);
		ft_putendl_fd(info_log, 2);
		return (-1);
	}
	*shader_ref = shader_tmp;
	return (0);
}

static unsigned int	link_shader(unsigned int *program_ref, \
	unsigned int shader_vertex, unsigned int shader_fragment)
{
	unsigned int	program_tmp;
	int				success;
	char			info_log[512];

	program_tmp = glCreateProgram();
	glAttachShader(program_tmp, shader_vertex);
	glAttachShader(program_tmp, shader_fragment);
	glLinkProgram(program_tmp);
	glGetProgramiv(program_tmp, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program_tmp, 512, NULL, info_log);
		ft_putendl_fd("ERROR::SHADER::PROGRAM::LINKING_FAILED", 2);
		ft_putendl_fd(info_log, 2);
		return (-1);
	}
	glDeleteShader(shader_vertex);
	glDeleteShader(shader_fragment);
	*program_ref = program_tmp;
	return (0);
}
