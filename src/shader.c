/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:22:21 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/09 14:45:21 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

unsigned int		load_shader(void)
{
	static const char		*vertex_shader_source = "#version 400 core\n" \
	"layout (location = 0) in vec3 aPos;\n" \
	"void main()\n" \
	"{\n" \
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" \
	"}\0";
	static const char		*fragment_shader_source = "#version 400 core\n" \
	"out vec4 FragColor;\n" \
	"void main()\n" \
	"{\n" \
	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" \
	"}\0";
	unsigned int			vertex_shader;
	unsigned int			fragment_shader;
	unsigned int			shader_program;
	int						success;
	char					info_log[512];

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		ft_putendl_fd("ERROR::SHADER::VERTEX::COMPILATION_FAILED", 2);
		ft_putendl_fd(info_log, 2);
	}
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		ft_putendl_fd("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED", 2);
		ft_putendl_fd(info_log, 2);
	}
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		ft_putendl_fd("ERROR::SHADER::LINK_FAILED", 2);
		ft_putendl_fd(info_log, 2);
	}
	glUseProgram(shader_program);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	return (shader_program);
}
