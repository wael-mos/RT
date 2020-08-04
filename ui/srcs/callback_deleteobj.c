/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_deleteobj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:18:56 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/09 13:28:21 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		reset_boxes(t_env *env, int type)
{
	if (type == 1)
	{
		env->scene.num_obj -= 1;
		create_oids(&env->scene);
		gtk_combo_box_text_remove_all((GtkComboBoxText *)env->gtk.objectlist);
		gtk_combo_box_text_insert_text((GtkComboBoxText *)env->gtk.objectlist, \
			-1, (const gchar *)"None");
		init_objectbox(env);
		env->scene.selected_obj = -1;
	}
	else
	{
		env->scene.num_light -= 1;
		create_lids(&env->scene);
		gtk_combo_box_text_remove_all((GtkComboBoxText *)env->gtk.lightbox);
		gtk_combo_box_text_insert_text((GtkComboBoxText *)env->gtk.lightbox, \
			-1, (const gchar *)"None");
		init_lightbox(env);
		env->scene.selected_light = -1;
	}
}

gboolean	delete_anobj(GtkButton *btn, gpointer data)
{
	t_env	*env;
	int		i;

	(void)btn;
	env = data;
	if (env->scene.selected_obj > -1)
	{
		blocker_master(env);
		gtk_widget_hide(env->gtk.objss);
		gtk_widget_hide(env->gtk.objs);
		i = 0;
		while (env->scene.selected_obj + i < env->scene.num_obj - 1)
		{
			env->scene.objs[env->scene.selected_obj + i] = \
						env->scene.objs[env->scene.selected_obj + i + 1];
			++i;
		}
		ft_bzero(&env->scene.objs[env->scene.num_obj - 1], sizeof(t_obj));
		reset_boxes(env, 1);
		unblocker_master(env);
		cl_run_kernel(env);
	}
	return (FALSE);
}

gboolean	delete_alight(GtkButton *btn, gpointer data)
{
	t_env	*env;
	int		i;

	(void)btn;
	env = data;
	if (env->scene.selected_light > -1)
	{
		blocker_master(env);
		gtk_widget_hide(env->gtk.lightsarea);
		i = 0;
		while (env->scene.selected_light + i < env->scene.num_light - 1)
		{
			env->scene.lights[env->scene.selected_light + i] = \
						env->scene.lights[env->scene.selected_light + i + 1];
			++i;
		}
		ft_bzero(&env->scene.lights[env->scene.num_light - 1], sizeof(t_light));
		reset_boxes(env, 2);
		unblocker_master(env);
		cl_run_kernel(env);
	}
	return (FALSE);
}
