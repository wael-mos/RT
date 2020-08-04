/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:46:01 by evogel            #+#    #+#             */
/*   Updated: 2020/07/20 22:52:11 by wael-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char		*read_code(char *file_name, t_env *env)
{
	int		fd;
	int		ret;
	char	buff[BUFF_SIZE + 1];
	char	*code;
	char	*tmp;

	code = ft_strnew(0);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		cl_error(env, "Could not open source code file.");
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0 && code != NULL)
	{
		buff[ret] = '\0';
		tmp = code;
		code = ft_strjoin(code, buff);
		free(tmp);
	}
	if (ret < 0 || code == NULL)
		cl_error(env, "Could not read source code file.");
	return (code);
}

static void		cl_build_kernel(t_env *env)
{
	cl_int		err;
	const char	*source_code;
	char		buffer[CL_ERROR_BUFF];

	source_code = read_code(CL_KERNEL_SOURCE, env);
	env->cl.program = clCreateProgramWithSource(env->cl.context, 1, \
			&source_code, NULL, &err);
	if (err != CL_SUCCESS)
		cl_error(env, "Creating program with source failed.");
	err = clBuildProgram(env->cl.program, 1, &env->cl.device_id, \
			CL_COMPILE_FLAGS, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		clGetProgramBuildInfo(env->cl.program, env->cl.device_id,
				CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, NULL);
		ft_printf("%s\n", buffer);
		cl_error(env, "Unable to build program.");
	}
	env->cl.kernel = clCreateKernel(env->cl.program, "render_scene", &err);
	if (err != CL_SUCCESS)
		cl_error(env, "Could not create kernel 'render_scene'.");
	free((void*)source_code);
}

static void		cl_create_queue(t_env *env)
{
	cl_platform_id		platform_id;
	cl_int				err;

	platform_id = NULL;
	err = clGetPlatformIDs(1, &platform_id, NULL);
	if (err != CL_SUCCESS)
		cl_error(env, "Could not get platform ID.");
	err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, \
			&env->cl.device_id, NULL);
	if (err != CL_SUCCESS)
	{
		err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, \
		&env->cl.device_id, NULL);
		(err == CL_SUCCESS) ? ft_printf("Running OpenCL on CPU.\n") :\
			cl_error(env, "Could not get GPU or CPU device ID.");
	}
	env->cl.context = clCreateContext(NULL, 1, &env->cl.device_id, NULL, NULL, \
			&err);
	if (err != CL_SUCCESS)
		cl_error(env, "Could not create context.");
	env->cl.command_queue = clCreateCommandQueue(env->cl.context, \
			env->cl.device_id, 0, &err);
	if (err != CL_SUCCESS)
		cl_error(env, "Could not create command queue.");
}

void			cl_init(t_env *env)
{
	cl_create_queue(env);
	cl_build_kernel(env);
	cl_prepare_mem(env);
}
