/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_effect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:20:25 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/21 10:50:33 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	change_saturation(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.saturation = (float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_gamma(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.gamma = (float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

void		effect_sepia(GtkSwitch *btn, GParamSpec *pspec, gpointer data)
{
	t_env *env;

	env = data;
	(void)pspec;
	if (gtk_switch_get_active(btn) == 1)
	{
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.effgrayscale), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_grayscale, NULL);
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.effinverted), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_inverted, NULL);
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.effcell), \
		G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_cellshading, NULL);
		env->scene.effect = 1;
		change_effswitch_state(env);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effgrayscale), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_grayscale, NULL);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effinverted), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_inverted, NULL);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effcell), \
		G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_cellshading, NULL);
	}
	else
		env->scene.effect = 0;
	cl_run_kernel(env);
}

void		effect_grayscale(GtkSwitch *btn, GParamSpec *pspec, gpointer data)
{
	t_env *env;

	env = data;
	(void)pspec;
	if (gtk_switch_get_active(btn) == 1)
	{
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.effsepia), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_sepia, NULL);
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.effinverted), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_inverted, NULL);
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.effcell), \
		G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_cellshading, NULL);
		env->scene.effect = 2;
		change_effswitch_state(env);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effsepia), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_sepia, NULL);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effinverted), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_inverted, NULL);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effcell), \
		G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_cellshading, NULL);
	}
	else
		env->scene.effect = 0;
	cl_run_kernel(env);
}

void		effect_inverted(GtkSwitch *btn, GParamSpec *pspec, gpointer data)
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
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.effcell), \
		G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_cellshading, NULL);
		env->scene.effect = 3;
		change_effswitch_state(env);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effgrayscale), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_grayscale, NULL);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effsepia), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_sepia, NULL);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.effcell), \
		G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)effect_cellshading, NULL);
	}
	else
		env->scene.effect = 0;
	cl_run_kernel(env);
}
