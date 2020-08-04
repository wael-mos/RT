/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_object3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:30:56 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/29 10:36:55 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	change_refl(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].refl = \
								(float)gtk_spin_button_get_value(btn) / 100;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_refr(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].refr = \
								(float)gtk_spin_button_get_value(btn) / 100;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_ior(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].ior = \
								(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_radius(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	if (env->scene.objs[env->scene.selected_obj].type == CONE)
		env->scene.objs[env->scene.selected_obj].rad = \
						(float)gtk_spin_button_get_value(btn) * M_PI / 180.f;
	else
		env->scene.objs[env->scene.selected_obj].rad = \
						(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

void		obj_hide_show(t_env *env, int i)
{
	gtk_widget_show_now(env->gtk.swbox);
	gtk_widget_show_now(env->gtk.infbox);
	gtk_widget_show_now(env->gtk.heightbox);
	gtk_widget_hide(env->gtk.checkbox);
	if (env->scene.objs[i].type != PLANE && env->scene.objs[i].type \
			!= DISK)
		gtk_widget_hide(env->gtk.swbox);
	if (env->scene.objs[i].type == SPHERE || env->scene.objs[i].type == PLANE\
	|| env->scene.objs[i].type == DISK || env->scene.objs[i].type == CYLINDER \
	|| env->scene.objs[i].type == CONE || env->scene.objs[i].type == CUBE)
	{
		pattern_hider(env, i);
		if (env->scene.objs[i].type == SPHERE || env->scene.objs[i].type == \
		PLANE || env->scene.objs[i].type == DISK || env->scene.objs[i].type == \
		CUBE)
		{
			gtk_widget_hide(env->gtk.infbox);
			gtk_widget_hide(env->gtk.heightbox);
		}
	}
	gtk_widget_show_now(env->gtk.objss);
	gtk_widget_show_now(env->gtk.objs);
}
