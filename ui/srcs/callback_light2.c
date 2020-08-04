/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_light2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:27:41 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/29 11:23:22 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_lightbox(t_env *env)
{
	int i;

	i = 0;
	while (i < env->scene.num_light)
	{
		gtk_combo_box_text_insert((GtkComboBoxText *)env->gtk.lightbox, \
				(gint)i, (gchar *)env->scene.lights[i].id, \
				(const gchar *)env->scene.lights[i].id);
		++i;
	}
}

gboolean	change_ambient(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.ambient = (float)gtk_spin_button_get_value(btn) / 100;
	cl_run_kernel(env);
	return (TRUE);
}
