/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widget_init2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:45:53 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/29 13:40:51 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	widget_init_camera(t_env *env)
{
	env->gtk.camposx = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"xpos1"));
	env->gtk.camposy = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"ypos1"));
	env->gtk.camposz = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"zpos1"));
	env->gtk.camrotx = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"xrot1"));
	env->gtk.camroty = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"yrot1"));
	env->gtk.camrotz = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"zrot1"));
	env->gtk.fov = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"fov"));
}

void	widget_init_effect(t_env *env)
{
	env->gtk.desaturate = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"saturation"));
	env->gtk.gamma = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"gamma"));
	env->gtk.ambient = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"ambient"));
	env->gtk.bounce = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"bounce"));
	env->gtk.effsepia = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"effsepia"));
	env->gtk.effgrayscale = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder,\
				"effgrayscale"));
	env->gtk.effinverted = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"effinverted"));
	env->gtk.effcell = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"effcell"));
	env->gtk.bgr = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
	"bgr"));
	env->gtk.bgg = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
	"bgg"));
	env->gtk.bgb = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
	"bgb"));
}

void	widget_init_lists(t_env *env)
{
	env->gtk.objectlist = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"objectslist"));
	env->gtk.deleteobj = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"deleteobj"));
	env->gtk.deletelight = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"deletelight"));
	env->gtk.objss = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"objstackswitcher"));
	env->gtk.objs = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"objstack"));
	env->gtk.swbox = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"swbox"));
	env->gtk.checkbox = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"checkbox"));
	env->gtk.lightsarea = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"lightsarea"));
}

void	widget_init_objpart1(t_env *env)
{
	env->gtk.xpos = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"xpos"));
	env->gtk.ypos = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"ypos"));
	env->gtk.zpos = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"zpos"));
	env->gtk.xrot = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"xrot"));
	env->gtk.yrot = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"yrot"));
	env->gtk.zrot = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"rotz"));
	env->gtk.height = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"height"));
	env->gtk.infswitch = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"infobject"));
	env->gtk.specular = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"specular"));
}

void	widget_init_objpart2(t_env *env)
{
	env->gtk.radius = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"radius"));
	env->gtk.reflectionset = GTK_WIDGET(\
		gtk_builder_get_object(env->gtk.builder, "reflectionset"));
	env->gtk.refrset = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"refrset"));
	env->gtk.ior = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"ior"));
	env->gtk.checkh = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"checkh"));
	env->gtk.checkw = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"checkw"));
	env->gtk.objr = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
	"objr"));
	env->gtk.objg = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
	"objg"));
	env->gtk.objb = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
	"objb"));
	env->gtk.checkr = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
	"checkr"));
	env->gtk.checkg = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
	"checkg"));
	env->gtk.checkb = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
	"checkb"));
}
