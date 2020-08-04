/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_addobj3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:14:20 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/30 16:59:01 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_new_scene(t_env *env, int state)
{
	ft_bzero(&env->scene, sizeof(t_scene));
	if (state == 1)
	{
		gtk_combo_box_text_remove_all((GtkComboBoxText *)env->gtk.objectlist);
		gtk_combo_box_text_remove_all((GtkComboBoxText *)env->gtk.lightbox);
		gtk_combo_box_text_insert_text((GtkComboBoxText *)env->gtk.objectlist, \
				-1, (const gchar *)"None");
		gtk_combo_box_text_insert_text((GtkComboBoxText *)env->gtk.lightbox, \
				-1, (const gchar *)"None");
	}
	env->scene.win_x = 1445;
	env->scene.win_y = 1008;
	env->scene.cam.pos = vec(0, 200.f, 1000.f);
	env->scene.cam.fov = 60.f;
	env->scene.saturation = 1;
	env->scene.gamma = 1;
	env->scene.ambient = 0.2;
	env->scene.selected_obj = -1;
	env->scene.selected_light = -1;
	env->scene.num_obj = 0;
	env->scene.num_light = 0;
	env->scene.bouncenb = 1;
	env->scene.fogdist = 0;
	env->scene.fogcol = vec(1.f, 1.f, 1.f);
}

gboolean	new_scene(GtkButton *btn, gpointer data)
{
	t_env	*env;

	(void)btn;
	env = data;
	if (env->scene.num_obj > 0 && env->scene.num_light > 0)
	{
		blocker_master(env);
		gtk_widget_hide(env->gtk.objss);
		gtk_widget_hide(env->gtk.objs);
		gtk_widget_hide(env->gtk.lightsarea);
		init_new_scene(env, 1);
		unblocker_master(env);
		cl_run_kernel(env);
		return (TRUE);
	}
	return (FALSE);
}

gboolean	add_sphere(GtkButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	(void)btn;
	if (add_object(env, SPHERE))
		return (FALSE);
	return (TRUE);
}

gboolean	add_tore(GtkButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	(void)btn;
	if (add_object(env, TORE))
		return (FALSE);
	return (TRUE);
}

gboolean	add_goursat(GtkButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	(void)btn;
	if (add_object(env, CUBE))
		return (FALSE);
	return (TRUE);
}
