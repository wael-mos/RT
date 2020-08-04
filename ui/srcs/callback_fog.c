/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_fog.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:21:57 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/30 16:40:00 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	change_fogr(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.fogcol.z = (float)gtk_spin_button_get_value(btn) / 255;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_fogg(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.fogcol.y = (float)gtk_spin_button_get_value(btn) / 255;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_fogb(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.fogcol.x = (float)gtk_spin_button_get_value(btn) / 255;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_fogdist(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.fogdist = (float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

void		init_fog_values(t_env *env)
{
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.fogr, \
			(gdouble)env->scene.fogcol.z);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.fogg, \
			(gdouble)env->scene.fogcol.y);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.fogb, \
			(gdouble)env->scene.fogcol.x);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.fogdist, \
			(gdouble)env->scene.fogdist);
}
