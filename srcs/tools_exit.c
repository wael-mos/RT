/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:31:37 by evogel            #+#    #+#             */
/*   Updated: 2020/07/13 13:57:49 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		our_exit(t_env *env, int status, char *msg)
{
	if (msg)
		ft_printf("%s\n", msg);
	if (env)
		cl_cleanup(&env->cl);
	exit(status);
}

gboolean	cross_exit(GtkWidget *widget, gpointer data)
{
	(void)widget;
	our_exit(data, 0, NULL);
	return (TRUE);
}
