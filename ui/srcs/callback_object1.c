/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_object1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:28:07 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/30 10:53:07 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_general(t_env *env, int i)
{
	blocker_master(env);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.xpos, \
			(gdouble)env->scene.objs[i].pos.x);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.ypos, \
			(gdouble)env->scene.objs[i].pos.y);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.zpos, \
			(gdouble)env->scene.objs[i].pos.z);
	if (env->scene.objs[i].type == CONE)
		gtk_spin_button_set_value((GtkSpinButton *)env->gtk.radius, \
				(gdouble)env->scene.objs[i].rad * 180 / M_PI);
	else
		gtk_spin_button_set_value((GtkSpinButton *)env->gtk.radius, \
				(gdouble)env->scene.objs[i].rad);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.xrot, \
			(gdouble)(env->scene.objs[i].rot.x * 180 / M_PI));
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.yrot, \
			(gdouble)(env->scene.objs[i].rot.y * 180 / M_PI));
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.zrot, \
			(gdouble)(env->scene.objs[i].rot.z * 180 / M_PI));
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.height, \
			(gdouble)env->scene.objs[i].height);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.specular, \
			(gdouble)env->scene.objs[i].shine);
	unblocker_master(env);
}

void		init_material2(t_env *env, int i)
{
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.reflectionset, \
			(gdouble)env->scene.objs[i].refl * 100);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.refrset, \
			(gdouble)env->scene.objs[i].refr * 100);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.ior, \
			(gdouble)env->scene.objs[i].ior);
	gtk_switch_set_active((GtkSwitch*)env->gtk.infswitch, (gboolean)\
			env->scene.objs[i].inf);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.objr, \
	(gdouble)env->scene.objs[i].col.z * 255);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.objg, \
	(gdouble)env->scene.objs[i].col.y * 255);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.objb, \
	(gdouble)env->scene.objs[i].col.x * 255);
}

void		init_material(t_env *env, int i)
{
	blocker_master(env);
	init_material2(env, i);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.checkh, \
			(gdouble)env->scene.objs[i].checkh);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.checkw, \
			(gdouble)env->scene.objs[i].checkw);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.checkr, \
	(gdouble)env->scene.objs[i].checkcol.z * 255);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.checkg, \
	(gdouble)env->scene.objs[i].checkcol.y * 255);
	gtk_spin_button_set_value((GtkSpinButton *)env->gtk.checkb, \
	(gdouble)env->scene.objs[i].checkcol.x * 255);
	unblocker_master(env);
}

gboolean	init_selectedobject_values(GtkComboBoxText *cbbt, gpointer data)
{
	char	*id;
	int		i;
	t_env	*env;

	env = data;
	id = (char *)gtk_combo_box_text_get_active_text(cbbt);
	if (!ft_strcmp(id, "None"))
	{
		env->scene.selected_obj = -1;
		gtk_widget_hide(env->gtk.objss);
		gtk_widget_hide(env->gtk.objs);
		free(id);
		return (FALSE);
	}
	else if (env->scene.num_obj > 0)
	{
		i = 0;
		while (ft_strcmp(id, env->scene.objs[i].id))
			++i;
		init_obj(env, i);
	}
	free(id);
	return (TRUE);
}

gboolean	move_objx(GtkSpinButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	env->scene.objs[env->scene.selected_obj].pos.x = \
		(float)gtk_spin_button_get_value(btn);
	cl_run_kernel(env);
	return (TRUE);
}
