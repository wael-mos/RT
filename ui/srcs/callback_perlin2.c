/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_perlin2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:41:31 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/09 11:42:07 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	perlin_opacity(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].perlin.opacity = \
								(float)gtk_spin_button_get_value(btn) / 100;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	perlin_turbpow(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].perlin.turbpow = \
								(float)gtk_spin_button_get_value(btn) / 100;
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	perlin_ringnb(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].perlin.ringnb = \
										(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	perlin_linex(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].perlin.linex = \
										(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}

gboolean	perlin_liney(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].perlin.liney = \
										(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}
