/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_object8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 15:28:15 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/30 10:49:55 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	change_lightg(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.lights[env->scene.selected_light].col.y = \
						(float)gtk_spin_button_get_value(btn) / 255;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	change_lightb(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.lights[env->scene.selected_light].col.x = \
							(float)gtk_spin_button_get_value(btn) / 255;
	cl_run_kernel(env);
	return (TRUE);
}
