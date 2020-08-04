/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_init2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:23:11 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/09 11:23:56 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	callback_init_effect(t_env *env)
{
	g_signal_connect(GTK_SWITCH(env->gtk.effsepia), \
			"notify::active", G_CALLBACK(effect_sepia), (gpointer)env);
	g_signal_connect(GTK_SWITCH(env->gtk.effgrayscale), \
			"notify::active", G_CALLBACK(effect_grayscale), (gpointer)env);
	g_signal_connect(GTK_SWITCH(env->gtk.effinverted), \
			"notify::active", G_CALLBACK(effect_inverted), (gpointer)env);
	g_signal_connect(GTK_SWITCH(env->gtk.effcell), \
			"notify::active", G_CALLBACK(effect_cellshading), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.ambient), \
			"value-changed", G_CALLBACK(change_ambient), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.bounce), \
			"value-changed", G_CALLBACK(change_bounce), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.desaturate), \
			"value-changed", G_CALLBACK(change_saturation), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.gamma), \
			"value-changed", G_CALLBACK(change_gamma), (gpointer)env);
}

void	callback_init_light(t_env *env)
{
	g_signal_connect(GTK_WIDGET(env->gtk.lightposx), \
			"value-changed", G_CALLBACK(move_lightx), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.lightposy), \
			"value-changed", G_CALLBACK(move_lighty), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.lightposz), \
			"value-changed", G_CALLBACK(move_lightz), (gpointer)env);
}

void	callback_init_perlin(t_env *env)
{
	g_signal_connect(GTK_SWITCH(env->gtk.perlinwood), \
			"notify::active", G_CALLBACK(perlin_wood), (gpointer)env);
	g_signal_connect(GTK_SWITCH(env->gtk.perlinmarble), \
			"notify::active", G_CALLBACK(perlin_marble), (gpointer)env);
	g_signal_connect(GTK_SWITCH(env->gtk.perlincloud), \
			"notify::active", G_CALLBACK(perlin_cloud), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.scaler), \
			"value-changed", G_CALLBACK(perlin_scaler), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.opacity), \
			"value-changed", G_CALLBACK(perlin_opacity), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.octave), \
			"value-changed", G_CALLBACK(perlin_octave), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.turbpow), \
			"value-changed", G_CALLBACK(perlin_turbpow), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.ringnb), \
			"value-changed", G_CALLBACK(perlin_ringnb), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.linex), \
			"value-changed", G_CALLBACK(perlin_linex), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.liney), \
			"value-changed", G_CALLBACK(perlin_liney), (gpointer)env);
}

void	callback_init_master(t_env *env)
{
	callback_init_button1(env);
	callback_init_button2(env);
	callback_init_objpart1(env);
	callback_init_objpart2(env);
	callback_init_camera(env);
	callback_init_effect(env);
	callback_init_light(env);
	callback_init_perlin(env);
}
