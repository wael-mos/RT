/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_addobj2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:12:19 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/28 15:32:08 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	add_cone(GtkButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	(void)btn;
	if (add_object(env, CONE))
		return (FALSE);
	return (TRUE);
}

gboolean	add_para(GtkButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	(void)btn;
	if (add_object(env, PARA))
		return (FALSE);
	return (TRUE);
}

gboolean	add_plane(GtkButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	(void)btn;
	if (add_object(env, 0))
		return (FALSE);
	return (TRUE);
}

gboolean	add_disk(GtkButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	(void)btn;
	if (add_object(env, DISK))
		return (FALSE);
	return (TRUE);
}

gboolean	new_light(GtkButton *btn, gpointer data)
{
	t_env	*env;
	t_light	new;

	env = data;
	(void)btn;
	if (env->scene.num_light < MAX_LIGHTS)
	{
		new = create_light();
		env->scene.lights[env->scene.num_light] = new;
		++env->scene.num_light;
		create_lids(&env->scene);
		gtk_combo_box_text_insert((GtkComboBoxText *)env->gtk.lightbox, \
				(gint)env->scene.num_light - 1, \
				(gchar *)env->scene.lights[env->scene.num_light - 1].id, \
				(const gchar *)env->scene.lights[env->scene.num_light - 1].id);
		cl_run_kernel(env);
		return (TRUE);
	}
	return (FALSE);
}
