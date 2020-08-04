/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_effect2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 15:36:37 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/29 11:24:15 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		change_effswitch_state(t_env *env)
{
	if (env->scene.effect == 1)
	{
		gtk_switch_set_active((GtkSwitch*)env->gtk.effgrayscale, FALSE);
		gtk_switch_set_active((GtkSwitch*)env->gtk.effcell, FALSE);
		gtk_switch_set_active((GtkSwitch*)env->gtk.effinverted, FALSE);
	}
	else if (env->scene.effect == 2)
	{
		gtk_switch_set_active((GtkSwitch*)env->gtk.effsepia, FALSE);
		gtk_switch_set_active((GtkSwitch*)env->gtk.effcell, FALSE);
		gtk_switch_set_active((GtkSwitch*)env->gtk.effinverted, FALSE);
	}
	else if (env->scene.effect == 3)
	{
		gtk_switch_set_active((GtkSwitch*)env->gtk.effgrayscale, FALSE);
		gtk_switch_set_active((GtkSwitch*)env->gtk.effcell, FALSE);
		gtk_switch_set_active((GtkSwitch*)env->gtk.effsepia, FALSE);
	}
	else if (env->scene.effect == 4)
	{
		gtk_switch_set_active((GtkSwitch*)env->gtk.effgrayscale, FALSE);
		gtk_switch_set_active((GtkSwitch*)env->gtk.effinverted, FALSE);
		gtk_switch_set_active((GtkSwitch*)env->gtk.effsepia, FALSE);
	}
}

gboolean	change_bounce(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.bouncenb = (float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

void		effect_cellshading(GtkSwitch *btn, GParamSpec *pspec, gpointer data)
{
	t_env *env;

	env = data;
	(void)pspec;
	if (gtk_switch_get_active(btn) == 1)
	{
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.effgrayscale), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_grayscale, NULL);
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.effsepia), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_sepia, NULL);
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.effinverted), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_inverted, NULL);
		env->scene.effect = 4;
		change_effswitch_state(env);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effgrayscale), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_grayscale, NULL);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effsepia), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_sepia, NULL);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effinverted), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_inverted, NULL);
	}
	else
		env->scene.effect = 0;
	cl_run_kernel(env);
}

void		init_effects(t_env *env)
{
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.effgrayscale), \
		G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_grayscale, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.effsepia), \
		G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_sepia, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.effinverted), \
		G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_inverted, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.effcell), \
		G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_cellshading, NULL);
	if (env->scene.effect == 1)
		gtk_switch_set_active((GtkSwitch *)env->gtk.effsepia, TRUE);
	else if (env->scene.effect == 2)
		gtk_switch_set_active((GtkSwitch *)env->gtk.effgrayscale, TRUE);
	else if (env->scene.effect == 3)
		gtk_switch_set_active((GtkSwitch *)env->gtk.effinverted, TRUE);
	else if (env->scene.effect == 4)
		gtk_switch_set_active((GtkSwitch *)env->gtk.effcell, TRUE);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effgrayscale), \
		G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_grayscale, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effsepia), \
		G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_sepia, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effinverted), \
		G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_inverted, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effcell), \
		G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_cellshading, NULL);
}
