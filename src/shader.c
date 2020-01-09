/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:22:21 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/09 18:24:20 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"
#include "libft.h"
#include "utils_file.h"

unsigned int		load_shader(unsigned int *shader_program)
{
	const char				*src;
	unsigned int			vertex_shader;
	unsigned int			fragment_shader;

	read_file(&src, VERTEX_SHADER_FILE);
	if (compile_shader(&vertex_shader, src, GL_VERTEX_SHADER))
		return (-1);
	ft_memdel((void *)&src);
	read_file(&src, FRAGMENT_SHADER_FILE);
	if (compile_shader(&fragment_shader, src, GL_FRAGMENT_SHADER))
	{
		glDeleteShader(vertex_shader);
		return (-1);
	}
	ft_memdel((void *)&src);
	if (link_shader(shader_program, vertex_shader, fragment_shader))
	{
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
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
