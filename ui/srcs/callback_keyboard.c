/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:24:09 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/09 13:32:50 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		movement_handler(t_env *env, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_s)
		env->scene.cam.pos.z += 20;
	if (event->keyval == GDK_KEY_S)
		env->scene.cam.pos.z += 100;
	if (event->keyval == GDK_KEY_W)
		env->scene.cam.pos.z -= 100;
	if (event->keyval == GDK_KEY_w)
		env->scene.cam.pos.z -= 20;
	if (event->keyval == GDK_KEY_A)
		env->scene.cam.pos.x -= 100;
	if (event->keyval == GDK_KEY_a)
		env->scene.cam.pos.x -= 20;
	if (event->keyval == GDK_KEY_D)
		env->scene.cam.pos.x += 100;
	if (event->keyval == GDK_KEY_d)
		env->scene.cam.pos.x += 20;
	if (event->keyval == GDK_KEY_space)
		env->scene.cam.pos.y += 100;
	if (event->keyval == GDK_KEY_z)
		env->scene.cam.pos.y -= 100;
	init_camproperties_values(env);
	cl_run_kernel(env);
}

void		rotation_handler(t_env *env, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_Left && env->scene.cam.rot.y \
			<= 360 * M_PI / 180)
		env->scene.cam.rot.y += 1 * M_PI / 180;
	if (event->keyval == GDK_KEY_Right && env->scene.cam.rot.y >= -360 * \
			M_PI / 180)
		env->scene.cam.rot.y -= 1 * M_PI / 180;
	if (event->keyval == GDK_KEY_Up && env->scene.cam.rot.x \
			<= 360 * M_PI / 180)
		env->scene.cam.rot.x += 1 * M_PI / 180;
	if (event->keyval == GDK_KEY_Down && env->scene.cam.rot.x >= -360 * \
			M_PI / 180)
		env->scene.cam.rot.x -= 1 * M_PI / 180;
	if (event->keyval == GDK_KEY_Home && env->scene.cam.rot.z \
			<= 360 * M_PI / 180)
		env->scene.cam.rot.z += 1 * M_PI / 180;
	if (event->keyval == GDK_KEY_End && env->scene.cam.rot.z \
			>= -360 * M_PI / 180)
		env->scene.cam.rot.z -= 1 * M_PI / 180;
	init_camproperties_values(env);
	cl_run_kernel(env);
}

int			key_to_func(GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_S || event->keyval == GDK_KEY_W \
			|| event->keyval == GDK_KEY_A || event->keyval == GDK_KEY_D \
			|| event->keyval == GDK_KEY_space || \
			event->keyval == GDK_KEY_z \
			|| event->keyval == GDK_KEY_s || event->keyval == GDK_KEY_w \
			|| event->keyval == GDK_KEY_a || event->keyval == GDK_KEY_d)
		return (1);
	else if (event->keyval == GDK_KEY_Left || event->keyval == GDK_KEY_Right \
			|| event->keyval == GDK_KEY_Up || event->keyval == GDK_KEY_Down \
			|| event->keyval == GDK_KEY_Home || event->keyval == GDK_KEY_End)
		return (2);
	return (0);
}

gboolean	key_handler(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	t_env *env;

	env = data;
	(void)widget;
	if (key_to_func(event) == 1)
	{
		movement_handler(env, event);
		return (TRUE);
	}
	else if (key_to_func(event) == 2)
	{
		rotation_handler(env, event);
		return (TRUE);
	}
	else if (event->keyval == GDK_KEY_Escape)
	{
		our_exit(data, 0, NULL);
		return (TRUE);
	}
	return (FALSE);
}
