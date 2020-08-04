/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_init1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:21:57 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/30 16:19:36 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	callback_init_button1(t_env *env)
{
	g_signal_connect(GTK_WIDGET(env->gtk.screenshot), \
			"clicked", G_CALLBACK(screenshot), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.newscene), \
			"clicked", G_CALLBACK(new_scene), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.openfile), \
			"clicked", G_CALLBACK(openfile), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.savefile), \
			"clicked", G_CALLBACK(savefile), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.addsphere), \
			"clicked", G_CALLBACK(add_sphere), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.addcyl), \
			"clicked", G_CALLBACK(add_cyl), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.addcone), \
			"clicked", G_CALLBACK(add_cone), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.addplane), \
			"clicked", G_CALLBACK(add_plane), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.adddisk), \
			"clicked", G_CALLBACK(add_disk), (gpointer)env);
}

void	callback_init_button2(t_env *env)
{
	g_signal_connect(GTK_WIDGET(env->gtk.addpara), \
			"clicked", G_CALLBACK(add_para), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.addtore), \
			"clicked", G_CALLBACK(add_tore), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.addcube), \
			"clicked", G_CALLBACK(add_goursat), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.addlight), \
			"clicked", G_CALLBACK(new_light), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.deleteobj), \
			"clicked", G_CALLBACK(delete_anobj), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.deletelight), \
			"clicked", G_CALLBACK(delete_alight), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.checkg), \
	"value-changed", G_CALLBACK(change_checkg), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.bgb), \
	"value-changed", G_CALLBACK(change_bgb), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.fogr), \
	"value-changed", G_CALLBACK(change_fogr), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.fogg), \
	"value-changed", G_CALLBACK(change_fogg), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.fogb), \
	"value-changed", G_CALLBACK(change_fogb), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.fogdist), \
	"value-changed", G_CALLBACK(change_fogdist), (gpointer)env);
}

void	callback_init_objpart1(t_env *env)
{
	g_signal_connect(GTK_WIDGET(env->gtk.xpos), \
			"value-changed", G_CALLBACK(move_objx), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.ypos), \
			"value-changed", G_CALLBACK(move_objy), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.zpos), \
			"value-changed", G_CALLBACK(move_objz), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.xrot), \
			"value-changed", G_CALLBACK(rot_objx), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.yrot), \
			"value-changed", G_CALLBACK(rot_objy), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.zrot), \
			"value-changed", G_CALLBACK(rot_objz), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.radius), \
			"value-changed", G_CALLBACK(change_radius), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.checkw), \
			"value-changed", G_CALLBACK(change_checkw), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.objr), \
	"value-changed", G_CALLBACK(change_objr), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.objg), \
	"value-changed", G_CALLBACK(change_objg), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.objb), \
	"value-changed", G_CALLBACK(change_objb), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.checkr), \
	"value-changed", G_CALLBACK(change_checkr), (gpointer)env);
}

void	callback_init_objpart2(t_env *env)
{
	g_signal_connect(GTK_WIDGET(env->gtk.checkb), \
	"value-changed", G_CALLBACK(change_checkb), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.reflectionset), \
			"value-changed", G_CALLBACK(change_refl), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.refrset), \
			"value-changed", G_CALLBACK(change_refr), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.ior), \
			"value-changed", G_CALLBACK(change_ior), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.swfreq), \
			"value-changed", G_CALLBACK(sw_freq), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.swamp), \
			"value-changed", G_CALLBACK(sw_amp), (gpointer)env);
	g_signal_connect(GTK_SWITCH(env->gtk.swsea), \
			"notify::active", G_CALLBACK(sw_seamode), (gpointer)env);
	g_signal_connect(GTK_SWITCH(env->gtk.swlake), \
			"notify::active", G_CALLBACK(sw_lakemode), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.height), \
			"value-changed", G_CALLBACK(change_height), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.specular), \
			"value-changed", G_CALLBACK(change_specular), (gpointer)env);
	g_signal_connect(GTK_SWITCH(env->gtk.infswitch), \
			"notify::active", G_CALLBACK(change_infinite), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.checkh), \
			"value-changed", G_CALLBACK(change_checkh), (gpointer)env);
}

void	callback_init_camera(t_env *env)
{
	g_signal_connect(GTK_WIDGET(env->gtk.camposx), \
			"value-changed", G_CALLBACK(move_camx), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.camposy), \
			"value-changed", G_CALLBACK(move_camy), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.camposz), \
			"value-changed", G_CALLBACK(move_camz), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.camrotx), \
			"value-changed", G_CALLBACK(rot_camx), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.camroty), \
			"value-changed", G_CALLBACK(rot_camy), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.camrotz), \
			"value-changed", G_CALLBACK(rot_camz), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.fov), \
			"value-changed", G_CALLBACK(change_fov), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.lightr), \
	"value-changed", G_CALLBACK(change_lightr), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.lightg), \
	"value-changed", G_CALLBACK(change_lightg), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.lightb), \
	"value-changed", G_CALLBACK(change_lightb), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.bgr), \
	"value-changed", G_CALLBACK(change_bgr), (gpointer)env);
	g_signal_connect(GTK_WIDGET(env->gtk.bgg), \
	"value-changed", G_CALLBACK(change_bgg), (gpointer)env);
}
