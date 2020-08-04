/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_addobj1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:09:49 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/28 12:05:40 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		create_object2(t_obj *new)
{
	new->perlin.scaler = 0;
	new->perlin.opacity = 0;
	new->perlin.ringnb = 0;
	new->perlin.linex = 0;
	new->perlin.liney = 0;
	new->shine = 0;
	new->inf = 1;
	new->height = 300;
	new->checkh = 0;
	new->checkcol = vec(1.0f, 1.0f, 1.0f);
	new->checkw = 0;
}

t_obj		create_object(int id)
{
	t_obj new;

	new.type = id;
	new.pos = vec(0, 0, 0);
	if (new.type == CONE || new.type == PARA)
		new.rad = (new.type == CONE ? (20 * M_PI / 180.f) : 20);
	else
		new.rad = 150;
	new.rot = vec(0.0f, 0.0f, 0.0f);
	new.axe = get_axe(vec(0.0f, 0.0f, 0.0f));
	new.col = vec(1.0f, 1.0f, 1.0f);
	new.ior = 0;
	new.refl = 0;
	new.refr = 0;
	new.water.mode = 0;
	new.water.ampli = 0;
	new.water.frequency = 0;
	new.perlin.type = 0;
	new.perlin.octav = 0;
	new.perlin.turbpow = 0;
	create_object2(&new);
	return (new);
}

t_light		create_light(void)
{
	t_light new;

	new.pos = vec(0, 500, 500);
	new.col = vec(1, 1, 1);
	return (new);
}

int			add_object(t_env *env, int id)
{
	t_obj new;

	if (env->scene.num_obj < MAX_OBJECTS)
	{
		new = create_object(id);
		env->scene.objs[env->scene.num_obj] = new;
		++env->scene.num_obj;
		create_oids(&env->scene);
		gtk_combo_box_text_insert((GtkComboBoxText *)env->gtk.objectlist, \
				(gint)env->scene.num_obj - 1, \
				(gchar *)env->scene.objs[env->scene.num_obj - 1].id, \
				(const gchar *)env->scene.objs[env->scene.num_obj - 1].id);
		cl_run_kernel(env);
		return (0);
	}
	return (1);
}

gboolean	add_cyl(GtkButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	(void)btn;
	if (add_object(env, CYLINDER))
		return (FALSE);
	return (TRUE);
}
