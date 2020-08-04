/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_sinewave.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:43:19 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/09 11:43:50 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	sw_seamode(GtkSwitch *btn, GParamSpec *pspec, gpointer data)
{
	t_env *env;

	env = data;
	(void)pspec;
	if (gtk_switch_get_active(btn))
	{
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.swlake), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)sw_lakemode, NULL);
		env->scene.objs[env->scene.selected_obj].water.mode = 1;
		gtk_switch_set_active((GtkSwitch *)env->gtk.swlake, FALSE);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.swlake), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)sw_lakemode, NULL);
	}
	else
		env->scene.objs[env->scene.selected_obj].water.mode = 0;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	sw_lakemode(GtkSwitch *btn, GParamSpec *pspec, gpointer data)
{
	t_env *env;

	env = data;
	(void)pspec;
	if (gtk_switch_get_active(btn))
	{
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.swsea), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)sw_seamode, NULL);
		env->scene.objs[env->scene.selected_obj].water.mode = 2;
		gtk_switch_set_active((GtkSwitch *)env->gtk.swsea, FALSE);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.swsea), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)sw_seamode, NULL);
	}
	else
		env->scene.objs[env->scene.selected_obj].water.mode = 0;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	sw_freq(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].water.frequency = \
										(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	sw_amp(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].water.ampli = \
										(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

void		init_sinewave_values(t_env *env, int i)
{
	blocker_master(env);
	if (env->scene.objs[i].water.mode == 1)
	{
		gtk_switch_set_active((GtkSwitch *)env->gtk.swlake, FALSE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.swsea, TRUE);
	}
	else if (env->scene.objs[i].water.mode == 2)
	{
		gtk_switch_set_active((GtkSwitch *)env->gtk.swlake, TRUE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.swsea, FALSE);
	}
	else
	{
		gtk_switch_set_active((GtkSwitch *)env->gtk.swlake, FALSE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.swsea, FALSE);
	}
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.swfreq, \
			(gdouble)env->scene.objs[i].water.frequency);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.swamp, \
			(gdouble)env->scene.objs[i].water.ampli);
	unblocker_master(env);
}
