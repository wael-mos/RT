/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_object2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:30:02 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/09 11:30:41 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	move_objy(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].pos.y = \
									(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	move_objz(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].pos.z = \
									(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	rot_objx(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].rot.x = \
						(float)gtk_spin_button_get_value(btn) * M_PI / 180.f;
	env->scene.objs[env->scene.selected_obj].axe = \
						get_axe(env->scene.objs[env->scene.selected_obj].rot);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	rot_objy(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].rot.y = \
						(float)gtk_spin_button_get_value(btn) * M_PI / 180.f;
	env->scene.objs[env->scene.selected_obj].axe = \
						get_axe(env->scene.objs[env->scene.selected_obj].rot);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	rot_objz(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].rot.z = \
						(float)gtk_spin_button_get_value(btn) * M_PI / 180.f;
	env->scene.objs[env->scene.selected_obj].axe = \
						get_axe(env->scene.objs[env->scene.selected_obj].rot);
	cl_run_kernel(env);
	return (TRUE);
}
