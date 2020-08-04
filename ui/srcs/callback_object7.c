/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_object7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 15:28:15 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/30 10:49:50 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	change_checkb(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].checkcol.x = \
							(float)gtk_spin_button_get_value(btn) / 255;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_bgr(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.bg.z = (float)gtk_spin_button_get_value(btn) / 255;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_bgg(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.bg.y = (float)gtk_spin_button_get_value(btn) / 255;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_bgb(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.bg.x = (float)gtk_spin_button_get_value(btn) / 255;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_lightr(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.lights[env->scene.selected_light].col.z = \
						(float)gtk_spin_button_get_value(btn) / 255;
	cl_run_kernel(env);
	return (TRUE);
}
