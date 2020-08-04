/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_light1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:25:16 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/30 10:53:37 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_lval(t_env *env, int i)
{
	blocker_master(env);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.lightposx, \
			(gdouble)env->scene.lights[i].pos.x);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.lightposy, \
			(gdouble)env->scene.lights[i].pos.y);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.lightposz, \
			(gdouble)env->scene.lights[i].pos.z);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.lightr, \
	(gdouble)env->scene.lights[i].col.z * 255);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.lightg, \
	(gdouble)env->scene.lights[i].col.y * 255);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.lightb, \
	(gdouble)env->scene.lights[i].col.x * 255);
	unblocker_master(env);
	gtk_widget_show_now(env->gtk.lightsarea);
	env->scene.selected_light = i;
}

gboolean	init_selectedlight_values(GtkComboBoxText *cbbt, gpointer data)
{
	char	*id;
	int		i;
	t_env	*env;

	env = data;
	id = (char *)gtk_combo_box_text_get_active_text(cbbt);
	if (!ft_strcmp(id, "None"))
	{
		env->scene.selected_light = -1;
		gtk_widget_hide(env->gtk.lightsarea);
		free(id);
		return (FALSE);
	}
	else
	{
		if (env->scene.num_light > 0)
		{
			i = 0;
			while (ft_strcmp(id, env->scene.lights[i].id))
				++i;
			init_lval(env, i);
		}
	}
	free(id);
	return (TRUE);
}

gboolean	move_lightx(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.lights[env->scene.selected_light].pos.x = \
								(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	move_lighty(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.lights[env->scene.selected_light].pos.y = \
									(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	move_lightz(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.lights[env->scene.selected_light].pos.z = \
										(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}
