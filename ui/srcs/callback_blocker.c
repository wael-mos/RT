/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_blocker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:16:02 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/30 16:49:44 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	block_1(t_env *env)
{
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.objectlist), \
	G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)init_selectedobject_values, \
		NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.lightbox), \
	G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)init_selectedlight_values, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.ypos), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)move_objy, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.zpos), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)move_objz, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.xpos), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)move_objx, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.yrot), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)rot_objy, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.zrot), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)rot_objz, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.xrot), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)rot_objx, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.radius), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_radius, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.reflectionset), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_refl, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.refrset), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_refr, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.ior), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_ior, NULL);
}

void	block_2(t_env *env)
{
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.scaler), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_scaler, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.opacity), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_opacity, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.octave), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_octave, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.turbpow), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_turbpow, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.ringnb), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_ringnb, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.linex), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_linex, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.liney), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_liney, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.swfreq), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)sw_freq, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.swamp), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)sw_amp, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.lightposy), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)move_lighty, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.lightposz), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)move_lightz, NULL);
}

void	block_3(t_env *env)
{
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.lightposx), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)move_lightx, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.camposx), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)move_camx, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.camposy), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)move_camy, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.camposz), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)move_camz, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.camrotx), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)rot_camx, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.camroty), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)rot_camy, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.camrotz), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)rot_camz, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.fov), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_fov, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.ambient), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_ambient, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.bounce), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_bounce, NULL);
}

void	block_4(t_env *env)
{
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.height), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_height, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.checkw), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_checkw, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.checkh), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_checkh, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.perlinwood), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_wood, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.perlinmarble), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_marble, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.perlincloud), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)perlin_cloud, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.specular), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_specular, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.desaturate), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_saturation, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.gamma), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_gamma, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.infswitch), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_infinite, NULL);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.swsea), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)sw_seamode, NULL);
}

void	blocker_master(t_env *env)
{
	block_1(env);
	block_2(env);
	block_3(env);
	block_4(env);
	block_5(env);
	block_6(env);
	g_signal_handlers_block_matched(GTK_WIDGET(env->gtk.bgb), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_bgb, NULL);
}
