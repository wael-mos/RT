/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_openscene.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:32:51 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/30 15:29:37 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <dirent.h>

void		reset_oboxes(t_env *env)
{
	gtk_combo_box_text_remove_all((GtkComboBoxText *)env->gtk.objectlist);
	gtk_combo_box_text_remove_all((GtkComboBoxText *)env->gtk.lightbox);
	gtk_combo_box_text_insert_text((GtkComboBoxText *)env->gtk.objectlist, \
		-1, (const gchar *)"None");
	gtk_combo_box_text_insert_text((GtkComboBoxText *)env->gtk.lightbox, \
		-1, (const gchar *)"None");
}

gboolean	openfile(GtkButton *btn, gpointer data)
{
	t_env	*e;
	char	*file;
	char	*tp;

	e = data;
	(void)btn;
	tp = gtk_combo_box_text_get_active_text((GtkComboBoxText *)e->gtk.filelist);
	file = ft_strjoin("scenes/", tp);
	free(tp);
	if (ft_strcmp(file, "scenes/Choose a file") && e->scene.selected_obj == \
			-1 && e->scene.selected_light == -1)
	{
		blocker_master(e);
		ft_bzero(&e->scene, sizeof(t_scene));
		reset_oboxes(e);
		if (parsing(file, &e->scene) != SUCCESS)
			our_exit(e, EXIT_FAILURE, "Parsing error.");
		init_camproperties_values(e);
		init_objectbox(e);
		init_lightbox(e);
		unblocker_master(e);
		cl_run_kernel(e);
	}
	free(file);
	return (TRUE);
}

void		init_openfile_list(t_env *env)
{
	DIR				*d;
	struct dirent	*dir;
	int				i;

	i = 0;
	d = opendir("scenes");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (ft_strstr(dir->d_name, ".xml"))
			{
				gtk_combo_box_text_insert((GtkComboBoxText *)env->gtk.filelist,\
					(gint)i, (gchar *)dir->d_name, (const gchar *)dir->d_name);
				++i;
			}
		}
		closedir(d);
	}
}

gboolean	savefile(GtkButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	(void)btn;
	blocker_master(env);
	exporter_main(&env->scene);
	unblocker_master(env);
	return (TRUE);
}
