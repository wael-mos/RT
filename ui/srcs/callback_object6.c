/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_object6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 15:28:15 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/30 10:50:12 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	change_objr(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].col.z = \
					(float)gtk_spin_button_get_value(btn) / 255;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_objg(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].col.y = \
						(float)gtk_spin_button_get_value(btn) / 255;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_objb(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].col.x = \
						(float)gtk_spin_button_get_value(btn) / 255;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_checkr(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].checkcol.z = \
							(float)gtk_spin_button_get_value(btn) / 255;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_checkg(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].checkcol.y = \
							(float)gtk_spin_button_get_value(btn) / 255;
	cl_run_kernel(env);
	return (TRUE);
}
