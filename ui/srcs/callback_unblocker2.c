/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_unblocker2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:44:16 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/30 16:49:21 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	unblock_5(t_env *env)
{
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.swlake), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)sw_lakemode, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.objr), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_objr, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.objg), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_objg, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.objb), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_objb, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.checkr), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_checkr, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.checkg), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_checkg, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.checkb), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_checkb, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.lightr), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_lightr, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.lightg), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_lightg, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.lightb), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_lightb, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.bgr), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_bgr, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.bgg), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_bgg, NULL);
}

void	unblock_6(t_env *env)
{
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.fogr), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_fogr, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.fogg), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_fogg, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.fogb), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_fogb, NULL);
	g_signal_handlers_unblock_matched(GTK_WIDGET(env->gtk.fogdist), \
			G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)change_fogdist, NULL);
}
