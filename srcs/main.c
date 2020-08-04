/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:38:14 by evogel            #+#    #+#             */
/*   Updated: 2020/07/13 14:04:19 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_interface(t_env *env)
{
	widget_init_master(env);
	callback_init_master(env);
	init_camproperties_values(env);
	init_openfile_list(env);
}

static int	window_init(t_env *env, int argc, char **argv)
{
	env->gtk.data = malloc(sizeof(unsigned int) * \
	env->scene.win_x * env->scene.win_y);
	gtk_init(&argc, &argv);
	env->gtk.builder = gtk_builder_new();
	env->gtk.css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(env->gtk.css_provider, "ui/interface.css", \
		NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), \
	GTK_STYLE_PROVIDER(env->gtk.css_provider),\
	GTK_STYLE_PROVIDER_PRIORITY_USER);
	gtk_builder_add_from_file(env->gtk.builder, "ui/interface.glade", NULL);
	env->gtk.window = GTK_WIDGET(gtk_builder_get_object(env->gtk.builder, \
				"mainwindow"));
	gtk_builder_connect_signals(env->gtk.builder, NULL);
	env->gtk.render = GTK_IMAGE(gtk_builder_get_object(env->gtk.builder, \
				"render"));
	init_interface(env);
	g_signal_connect(G_OBJECT(env->gtk.window), \
			"key_press_event", G_CALLBACK(key_handler), env);
	g_signal_connect(G_OBJECT(env->gtk.window), "destroy", \
	G_CALLBACK(cross_exit), (gpointer)env);
	g_object_unref(env->gtk.builder);
	gtk_widget_show(env->gtk.window);
	return (0);
}

int			main(int ac, char **av)
{
	t_env	env;

	ft_bzero((void *)&env, sizeof(t_env));
	ft_putendl("Parsing the scene...");
	if (ac > 1 && parsing(av[1], &env.scene) != SUCCESS)
		our_exit(&env, EXIT_FAILURE, "Parsing error.");
	else if (ac == 1)
	{
		ft_putendl("No scene selected, creating a new one...");
		init_new_scene(&env, 0);
	}
	ft_putendl("GTK Initialization...");
	window_init(&env, ac, av);
	ft_putendl("OpenCL Initialization...");
	cl_init(&env);
	cl_run_kernel(&env);
	gtk_main();
	return (0);
}
