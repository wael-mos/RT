/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_camera1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:17:20 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/09 11:17:59 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float		rad2deg(float rad)
{
	return (rad * 180 / M_PI);
}

gboolean	move_camx(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.cam.pos.x = (float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	move_camy(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.cam.pos.y = (float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	move_camz(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.cam.pos.z = (float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	rot_camx(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.cam.rot.x = (float)gtk_spin_button_get_value(btn) * M_PI / 180;
	cl_run_kernel(env);
	return (TRUE);
}
