/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widget_init1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:44:57 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/30 16:18:21 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	widget_init_sinewave(t_env *env)
{
	env->gtk.swfreq = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"swfreq"));
	env->gtk.swamp = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"swamp"));
	env->gtk.swsea = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"swsea"));
	env->gtk.swlake = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"swlake"));
	env->gtk.addcube = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"addcube"));
	env->gtk.fogr = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"fogr"));
	env->gtk.fogg = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"fogg"));
	env->gtk.fogb = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"fogb"));
	env->gtk.fogdist = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"fogdist"));
}

void	widget_init_buttons1(t_env *env)
{
	env->gtk.screenshot = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"screenshot"));
	env->gtk.newscene = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"new"));
	env->gtk.openfile = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"openfile"));
	env->gtk.filelist = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"filelist"));
	env->gtk.savefile = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"save"));
	env->gtk.addsphere = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"addsphere"));
	env->gtk.addcyl = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"addcyl"));
	env->gtk.addcone = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"addcone"));
	env->gtk.addplane = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"addplane"));
	env->gtk.adddisk = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"adddisk"));
	env->gtk.addtore = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"addtore"));
}

void	widget_init_buttons2(t_env *env)
{
	env->gtk.addpara = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"addpara"));
	env->gtk.addlight = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"addlight"));
	env->gtk.checkbox = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"checkbox"));
	env->gtk.checktitle = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"checktitle"));
	env->gtk.checktitle = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"checktitle"));
	env->gtk.twtitle = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"twtitle"));
	env->gtk.thtitle = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"thtitle"));
	env->gtk.tcoltitle = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"tcoltitle"));
	env->gtk.infbox = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"infbox"));
	env->gtk.heightbox = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"heightbox"));
}

void	widget_init_perlin(t_env *env)
{
	env->gtk.scaler = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"scaler"));
	env->gtk.opacity = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"opacity"));
	env->gtk.octave = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"octave"));
	env->gtk.turbpow = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"turbpow"));
	env->gtk.ringnb = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"ringnb"));
	env->gtk.linex = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"linex"));
	env->gtk.liney = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"liney"));
	env->gtk.perlinwood = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"perlinwood"));
	env->gtk.perlincloud = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"perlincloud"));
	env->gtk.perlinmarble = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder,\
				"perlinmarble"));
}

void	widget_init_master(t_env *env)
{
	widget_init_light(env);
	widget_init_camera(env);
	widget_init_effect(env);
	widget_init_lists(env);
	init_objectbox(env);
	gtk_widget_hide(env->gtk.objss);
	gtk_widget_hide(env->gtk.objs);
	g_signal_connect(GTK_WIDGET(env->gtk.objectlist), \
			"changed", G_CALLBACK(init_selectedobject_values), (gpointer)env);
	env->gtk.lightbox = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"lightslist"));
	init_lightbox(env);
	g_signal_connect(GTK_WIDGET(env->gtk.lightbox), \
			"changed", G_CALLBACK(init_selectedlight_values), (gpointer)env);
	gtk_widget_hide(env->gtk.lightsarea);
	widget_init_objpart1(env);
	widget_init_objpart2(env);
	widget_init_sinewave(env);
	widget_init_buttons1(env);
	widget_init_buttons2(env);
	widget_init_perlin(env);
}
