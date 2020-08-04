/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_object4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:31:35 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/29 11:28:25 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	change_specular(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].shine = \
										(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

void		change_infinite(GtkSwitch *btn, GParamSpec *pspec, gpointer data)
{
	t_env *env;

	env = data;
	(void)pspec;
	env->scene.objs[env->scene.selected_obj].inf = \
										(int)gtk_switch_get_active(btn);
	cl_run_kernel(env);
}

gboolean	change_checkh(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].checkh = \
										(int)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_checkw(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].checkw = \
										(int)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_checkcol(GtkColorButton *btn, gpointer data)
{
	t_env	*env;
	GdkRGBA	gcol2;

	env = data;
	gtk_color_chooser_get_rgba((GtkColorChooser *)btn, &gcol2);
	env->scene.objs[env->scene.selected_obj].checkcol.x = gcol2.blue;
	env->scene.objs[env->scene.selected_obj].checkcol.y = gcol2.green;
	env->scene.objs[env->scene.selected_obj].checkcol.z = gcol2.red;
	cl_run_kernel(env);
	return (TRUE);
}
