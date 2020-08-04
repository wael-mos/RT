/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_perlin1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:40:52 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/09 15:33:42 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	perlin_scaler(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].perlin.scaler = \
							(float)gtk_spin_button_get_value(btn) / 10000;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	perlin_octave(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].perlin.octav = \
									(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	perlin_wood(GtkSwitch *btn, GParamSpec *pspec, gpointer data)
{
	t_env *env;

	env = data;
	(void)pspec;
	if (gtk_switch_get_active(btn))
	{
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.perlinmarble), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_marble, NULL);
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.perlincloud), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_cloud, NULL);
		gtk_widget_set_sensitive(env->gtk.ringnb, TRUE);
		gtk_widget_set_sensitive(env->gtk.linex, FALSE);
		gtk_widget_set_sensitive(env->gtk.liney, FALSE);
		env->scene.objs[env->scene.selected_obj].perlin.type = 1;
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlinmarble, FALSE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlincloud, FALSE);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.perlinmarble), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_marble, NULL);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.perlincloud), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_cloud, NULL);
	}
	else
		env->scene.objs[env->scene.selected_obj].perlin.type = 0;
	cl_run_kernel(env);
	return (TRUE);
}
