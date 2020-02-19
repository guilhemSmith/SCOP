/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:43:48 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/19 17:32:55 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_adv.h"
#include "renderer.h"
#include "scop.h"
#include "utils_scop.h"

static GLFWwindow	*init_opengl(void)
{
	GLFWwindow	*window;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	window = glfwCreateWindow(WIDTH_DEF, HEIGHT_DEF, "SCOP", NULL, NULL);
	if (window == NULL)
	{
		ft_putendl_fd("Failed to create GLFW window", 2);
		glfwTerminate();
		return (NULL);
	}
	glfwMakeContextCurrent(window);
	if (GLEW_OK != glewInit())
	{
		ft_putendl_fd("Failed to init GLEW:", 2);
		glfwSetWindowShouldClose(window, 1);
		return (NULL);
	}
	glViewport(0, 0, WIDTH_DEF, HEIGHT_DEF);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST);
	return (window);
}

static void			init_scop(t_render_config *config, t_obj_render *obj, \
	t_timer *timer, float camera_pos[3])
{
	*config = (t_render_config){{0, 0}, FOV_DEF, WIDTH_DEF, \
		HEIGHT_DEF, 0, 0, 0, 0};
	*obj = (t_obj_render){0, 0, 0, 0, 0, GL_TRIANGLES, 0, 36};
	*timer = (t_timer){0, 0};
	camera_pos[0] = 0;
	camera_pos[1] = 0;
	camera_pos[2] = -10;
}

static unsigned int	init_shaders(unsigned int shader[3])
{
	const float		obj_color[3] = {1, 0.5, 0.31};

	if (load_shader(&(shader[0]), VERTEX_FLAT, FRAGMENT_FLAT))
		return (-1);
	if (load_shader(&(shader[1]), VERTEX_TEXTURE, FRAGMENT_TEXTURE))
		return (-1);
	shader_set_vec3(shader[0], "object_color", obj_color);
	return (0);
}

int					main(int argc, char *argv[])
{
	GLFWwindow		*window;
	t_render_config	config;
	t_obj_render	obj;
	t_timer			timer;
	float			camera_pos[3];

	init_scop(&config, &obj, &timer, camera_pos);
	if ((window = init_opengl()) == NULL)
		return (-1);
	if (init_shaders(config.shader))
		return (close_soft(-1, config, obj));
	if (load_object(&obj, argc, argv) != 0)
		return (close_soft(-1, config, obj));
	if (load_texture(&(obj.texture), TEXTURE_PATH_RELATIVE))
		return (close_soft(-1, config, obj));
	while (!glfwWindowShouldClose(window))
	{
		timer.last = timer.current;
		timer.current = glfwGetTime();
		process_input(window, camera_pos, &config, timer.current - timer.last);
		render_object(config, obj, camera_pos);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return (close_soft(0, config, obj));
}
