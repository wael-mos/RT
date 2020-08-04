/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_object5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 15:28:15 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/29 14:10:40 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_objectbox(t_env *env)
{
	int i;

	i = 0;
	while (i < env->scene.num_obj)
	{
		gtk_combo_box_text_insert((GtkComboBoxText *)env->gtk.objectlist, \
				(gint)i, (gchar *)env->scene.objs[i].id, \
				(const gchar *)env->scene.objs[i].id);
		++i;
	}
}

gboolean	change_height(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].height = \
								(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

void		init_obj(t_env *env, int i)
{
	init_general(env, i);
	init_material(env, i);
	init_perlin_values(env, i);
	init_sinewave_values(env, i);
	env->scene.selected_obj = i;
	gtk_switch_set_active((GtkSwitch *)env->gtk.infswitch, \
			(gboolean)env->scene.objs[i].inf);
	obj_hide_show(env, i);
}

void		pattern_hider(t_env *env, int i)
{
	gtk_widget_show_now(env->gtk.checkbox);
	gtk_widget_hide(env->gtk.twtitle);
	gtk_widget_hide(env->gtk.checkw);
	if (env->scene.objs[i].type == SPHERE || env->scene.objs[i].type == PLANE \
			|| env->scene.objs[i].type == DISK)
	{
		gtk_label_set_text((GtkLabel *)env->gtk.checktitle, "Checkerboard");
		gtk_label_set_text((GtkLabel *)env->gtk.tcoltitle, "Tile Color");
		if (env->scene.objs[i].type == PLANE || env->scene.objs[i].type == DISK)
			gtk_label_set_text((GtkLabel *)env->gtk.thtitle, "Tile Size");
		else
		{
			gtk_label_set_text((GtkLabel *)env->gtk.thtitle, "Tile Width");
			gtk_widget_show_now(env->gtk.twtitle);
			gtk_widget_show_now(env->gtk.checkw);
		}
	}
	else if (env->scene.objs[i].type == CYLINDER || \
			env->scene.objs[i].type == CONE)
	{
		gtk_label_set_text((GtkLabel *)env->gtk.checktitle, "Stripes");
		gtk_label_set_text((GtkLabel *)env->gtk.thtitle, "Stripes Count");
		gtk_label_set_text((GtkLabel *)env->gtk.tcoltitle, "Stripes Color");
	}
}
