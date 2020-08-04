/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_camera2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:18:12 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/30 16:47:26 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	rot_camy(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.cam.rot.y = (float)gtk_spin_button_get_value(btn) * M_PI / 180;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	rot_camz(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.cam.rot.z = (float)gtk_spin_button_get_value(btn) * M_PI / 180;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_fov(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.cam.fov = (float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

void		init_camproperties_values2(t_env *env)
{
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.camposx, \
			(gdouble)env->scene.cam.pos.x);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.camposy, \
			(gdouble)env->scene.cam.pos.y);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.camposz, \
			(gdouble)env->scene.cam.pos.z);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.fov, \
			(gdouble)env->scene.cam.fov);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.ambient, \
			(gdouble)env->scene.ambient * 100);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.desaturate, \
			(gdouble)env->scene.saturation);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.gamma, \
			(gdouble)env->scene.gamma);
}

void		init_camproperties_values(t_env *env)
{
	blocker_master(env);
	init_camproperties_values2(env);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.camrotx, \
			(gdouble)rad2deg(env->scene.cam.rot.x));
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.camroty, \
			(gdouble)rad2deg(env->scene.cam.rot.y));
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.camrotz, \
			(gdouble)rad2deg(env->scene.cam.rot.z));
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.bounce, \
			(gdouble)env->scene.bouncenb);
	init_effects(env);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.bgr, \
			(gdouble)env->scene.bg.z * 255);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.bgg, \
			(gdouble)env->scene.bg.y * 255);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.bgb, \
			(gdouble)env->scene.bg.x * 255);
	init_fog_values(env);
	unblocker_master(env);
}
