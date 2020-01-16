/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:43:48 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/16 16:23:47 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
	*config = (t_render_config){0, FOV_DEF, WIDTH_DEF, HEIGHT_DEF, 0, 0, 0, 0};
	*obj = (t_obj_render){0, 0, GL_TRIANGLES, 0, 36};
	*timer = (t_timer){0, 0};
	camera_pos[0] = 0;
	camera_pos[1] = 0;
	camera_pos[2] = -3;
}

int					main(void)
{
	GLFWwindow		*window;
	t_render_config	config;
	t_obj_render	obj;
	t_timer			timer;
	float			camera_pos[3];

	init_scop(&config, &obj, &timer, camera_pos);
	if ((window = init_opengl()) == NULL)
		return (-1);
	if (load_shader(&(config.shader)))
		return (close_soft(-1, NULL));
	if ((obj.vao = load_object()) == 0)
		return (close_soft(-1, &(config.shader)));
	if (load_texture(&(obj.texture), TEXTURE_PATH_RELATIVE))
		return (close_soft(-1, &(config.shader)));
	while (!glfwWindowShouldClose(window))
	{
		timer.last = timer.current;
		timer.current = glfwGetTime();
		process_input(window, camera_pos, &config, timer.current - timer.last);
		render_object(config, obj, camera_pos);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return (close_soft(0, &(config.shader)));
}
