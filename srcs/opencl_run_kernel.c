/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_run_kernel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 12:01:05 by evogel            #+#    #+#             */
/*   Updated: 2020/07/13 14:02:15 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cl_cleanup(t_cl *cl)
{
	clReleaseMemObject(cl->scene);
	clReleaseMemObject(cl->img);
	clReleaseKernel(cl->kernel);
	clReleaseProgram(cl->program);
	clReleaseCommandQueue(cl->command_queue);
	clReleaseContext(cl->context);
}

void		cl_error(t_env *env, char *err_msg)
{
	ft_printf("OpenCL error: %s\n", err_msg);
	our_exit(env, EXIT_FAILURE, NULL);
}

void		cl_prepare_mem(t_env *env)
{
	cl_int	err;

	env->cl.scene = clCreateBuffer(env->cl.context, CL_MEM_READ_ONLY,
			sizeof(t_scene), NULL, NULL);
	env->cl.img = clCreateBuffer(env->cl.context, CL_MEM_WRITE_ONLY,
			sizeof(int) * env->scene.win_x * env->scene.win_y, NULL, NULL);
	if (!env->cl.scene || !env->cl.img)
		cl_error(env, "Failed to create memory buffers.");
	err = clSetKernelArg(env->cl.kernel, 0, sizeof(cl_mem), &env->cl.scene);
	err |= clSetKernelArg(env->cl.kernel, 1, sizeof(cl_mem), &env->cl.img);
	if (err != CL_SUCCESS)
		cl_error(env, "Failed to set kernel arguments.");
}

void		cl_run_kernel(t_env *env)
{
	cl_int	err;
	size_t	global_item_size[2];

	err = clEnqueueWriteBuffer(env->cl.command_queue, env->cl.scene, CL_TRUE, 0,
			sizeof(t_scene), &env->scene, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		cl_error(env, "Failed to write buffer data.");
	global_item_size[0] = (size_t)env->scene.win_x;
	global_item_size[1] = (size_t)env->scene.win_y;
	err = clEnqueueNDRangeKernel(env->cl.command_queue, env->cl.kernel, 2, NULL,
			global_item_size, NULL, 0, NULL, NULL);
	err = clEnqueueReadBuffer(env->cl.command_queue, env->cl.img, CL_TRUE, 0,
			sizeof(int) * env->scene.win_x * env->scene.win_y, env->gtk.data, \
			0, NULL, NULL);
	if (err == CL_SUCCESS)
	{
		env->gtk.image = gdk_pixbuf_new_from_data((const guchar *)\
		env->gtk.data, GDK_COLORSPACE_RGB, 1, 8, env->scene.win_x, \
		env->scene.win_y, env->scene.win_x * sizeof(unsigned int), NULL, NULL);
		gtk_image_set_from_pixbuf(env->gtk.render, env->gtk.image);
		g_object_unref(env->gtk.image);
	}
	else
		cl_error(env, "Failed to run kernel.");
}
