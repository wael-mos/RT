/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 22:45:38 by wael-mos          #+#    #+#             */
/*   Updated: 2020/07/20 22:45:48 by wael-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_cam(xmlNode *node, t_scene *scene)
{
	xmlNode *cur;
	xmlChar	*value;

	if (!node || !node->children)
		return ;
	if (node->properties)
	{
		if (ft_strequ((char *)node->properties->name, "fov"))
		{
			value = xmlNodeListGetString(node->doc,
					node->properties->children, 1);
			scene->cam.fov = ft_atoi((char *)value);
			xmlFree(value);
		}
	}
	cur = node->children;
	while (cur)
	{
		if (ft_strequ((char *)cur->name, "pos"))
			scene->cam.pos = parse_pos(cur);
		if (ft_strequ((char *)cur->name, "rot"))
			scene->cam.rot = deg(parse_pos(cur));
		cur = cur->next;
	}
	xmlFree(cur);
}

void		parse_windows_attr(xmlNode *cur, t_scene *scene)
{
	xmlAttr	*attr;
	xmlChar	*value;

	attr = NULL;
	value = NULL;
	attr = cur->properties;
	while (attr)
	{
		value = xmlNodeListGetString(cur->doc, attr->children, 1);
		scene->win_x = 1440;
		scene->win_y = 1008;
		if (ft_strequ((char *)attr->name, "value"))
			scene->bouncenb = ft_atoi((char *)value);
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
}

void		parse_windows(xmlNode *node, t_scene *scene)
{
	xmlNode *cur;

	if (!node || !node->children)
		return ;
	cur = node->children;
	while (cur)
	{
		if (ft_strequ((char *)cur->name, "size"))
			parse_windows_attr(cur, scene);
		else if (ft_strequ((char *)cur->name, "bouncenb"))
			parse_windows_attr(cur, scene);
		cur = cur->next;
	}
	xmlFree(cur);
}

void		parse_effects_attr(xmlNode *cur, t_scene *scene, int type)
{
	xmlAttr	*attr;
	xmlChar	*value;

	attr = NULL;
	value = NULL;
	attr = cur->properties;
	while (attr)
	{
		value = xmlNodeListGetString(cur->doc, attr->children, 1);
		if (type == 0)
			scene->effect = ft_atoi((char *)value);
		else if (type == 1)
			scene->saturation = (float)ft_atoi((char *)value) / 10;
		else if (type == 2)
			scene->gamma = (float)ft_atoi((char *)value) / 10;
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
}

void		parse_effects(xmlNode *node, t_scene *scene)
{
	xmlNode *cur;

	if (!node || !node->children)
		return ;
	cur = node->children;
	while (cur)
	{
		if (ft_strequ((char *)cur->name, "filter"))
			parse_effects_attr(cur, scene, 0);
		else if (ft_strequ((char *)cur->name, "background"))
			scene->bg = parse_col(cur);
		else if (ft_strequ((char *)cur->name, "saturation"))
			parse_effects_attr(cur, scene, 1);
		else if (ft_strequ((char *)cur->name, "gamma"))
			parse_effects_attr(cur, scene, 2);
		cur = cur->next;
	}
	xmlFree(cur);
}
