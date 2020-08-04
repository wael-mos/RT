/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_perlin3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:42:20 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/09 15:33:39 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	perlin_marble(GtkSwitch *btn, GParamSpec *pspec, gpointer data)
{
	t_env *env;

	env = data;
	(void)pspec;
	if (gtk_switch_get_active(btn))
	{
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.perlinwood), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_wood, NULL);
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.perlincloud), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_cloud, NULL);
		gtk_widget_set_sensitive(env->gtk.ringnb, FALSE);
		gtk_widget_set_sensitive(env->gtk.linex, TRUE);
		gtk_widget_set_sensitive(env->gtk.liney, TRUE);
		env->scene.objs[env->scene.selected_obj].perlin.type = 2;
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlinwood, FALSE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlincloud, FALSE);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.perlinwood), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_wood, NULL);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.perlincloud), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_cloud, NULL);
	}
	else
		env->scene.objs[env->scene.selected_obj].perlin.type = 0;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	perlin_cloud(GtkSwitch *btn, GParamSpec *pspec, gpointer data)
{
	t_env *env;

	env = data;
	(void)pspec;
	if (gtk_switch_get_active(btn))
	{
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.perlinwood), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_wood, NULL);
		g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.perlinmarble), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_marble, NULL);
		gtk_widget_set_sensitive(env->gtk.ringnb, FALSE);
		gtk_widget_set_sensitive(env->gtk.linex, FALSE);
		gtk_widget_set_sensitive(env->gtk.liney, FALSE);
		env->scene.objs[env->scene.selected_obj].perlin.type = 3;
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlinwood, FALSE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlinmarble, FALSE);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.perlinwood), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_wood, NULL);
		g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.perlinmarble), \
				G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_marble, NULL);
	}
	else
		env->scene.objs[env->scene.selected_obj].perlin.type = 0;
	cl_run_kernel(env);
	return (TRUE);
}

void		init_perlin_display2(t_env *env, int i)
{
	if (env->scene.objs[i].perlin.type == 3)
	{
		gtk_widget_set_sensitive(env->gtk.ringnb, FALSE);
		gtk_widget_set_sensitive(env->gtk.linex, FALSE);
		gtk_widget_set_sensitive(env->gtk.liney, FALSE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlinmarble, FALSE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlincloud, TRUE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlinwood, FALSE);
	}
	else
	{
		gtk_widget_set_sensitive(env->gtk.ringnb, FALSE);
		gtk_widget_set_sensitive(env->gtk.linex, FALSE);
		gtk_widget_set_sensitive(env->gtk.liney, FALSE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlinmarble, FALSE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlincloud, FALSE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlinwood, FALSE);
	}
}

void		init_perlin_display1(t_env *env, int i)
{
	if (env->scene.objs[i].perlin.type == 1)
	{
		gtk_widget_set_sensitive(env->gtk.ringnb, TRUE);
		gtk_widget_set_sensitive(env->gtk.linex, FALSE);
		gtk_widget_set_sensitive(env->gtk.liney, FALSE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlinmarble, FALSE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlincloud, FALSE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlinwood, TRUE);
	}
	else if (env->scene.objs[i].perlin.type == 2)
	{
		gtk_widget_set_sensitive(env->gtk.ringnb, FALSE);
		gtk_widget_set_sensitive(env->gtk.linex, TRUE);
		gtk_widget_set_sensitive(env->gtk.liney, TRUE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlinmarble, TRUE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlincloud, FALSE);
		gtk_switch_set_active((GtkSwitch *)env->gtk.perlinwood, FALSE);
	}
	else
		init_perlin_display2(env, i);
}

void		init_perlin_values(t_env *env, int i)
{
	blocker_master(env);
	init_perlin_display1(env, i);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.scaler, \
			(gdouble)env->scene.objs[i].perlin.scaler * 10000);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.opacity, \
			(gdouble)env->scene.objs[i].perlin.opacity * 100);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.octave, \
			(gdouble)env->scene.objs[i].perlin.octav);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.turbpow, \
			(gdouble)env->scene.objs[i].perlin.turbpow * 100);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.linex, \
			(gdouble)env->scene.objs[i].perlin.linex);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.liney, \
			(gdouble)env->scene.objs[i].perlin.liney);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.ringnb, \
			(gdouble)env->scene.objs[i].perlin.ringnb);
	unblocker_master(env);
}
