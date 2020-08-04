/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widget_init3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:46:55 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/29 13:40:21 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	widget_init_light(t_env *env)
{
	env->gtk.lightposx = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"xpos2"));
	env->gtk.lightposy = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"ypos2"));
	env->gtk.lightposz = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"zpos2"));
	env->gtk.lightr = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
	"lightr"));
	env->gtk.lightg = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
	"lightg"));
	env->gtk.lightb = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
	"lightb"));
}
