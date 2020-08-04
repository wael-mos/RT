/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 22:39:57 by wael-mos          #+#    #+#             */
/*   Updated: 2020/07/30 16:58:47 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		check_value(t_scene *scene)
{
	scene->win_x = 1445;
	scene->win_y = 1008;
	scene->saturation = (!scene->saturation) ? 1 : scene->saturation;
	scene->gamma = (!scene->gamma) ? 1 : scene->gamma;
	scene->selected_obj = -1;
	scene->selected_light = -1;
	scene->fogdist = 0.f;
	scene->fogcol.x = 1.f;
	scene->fogcol.y = 1.f;
	scene->fogcol.z = 1.f;
	scene->bg.x = (!scene->bg.x) ? 0.0f : scene->bg.x;
	scene->bg.y = (!scene->bg.y) ? 0.0f : scene->bg.y;
	scene->bg.z = (!scene->bg.z) ? 0.0f : scene->bg.z;
	scene->bouncenb = (!scene->bouncenb) ? 10 : scene->bouncenb;
}

cl_float3	parse_col(xmlNode *cur)
{
	xmlAttr		*attr;
	xmlChar		*value;
	cl_float3	col;

	if (!cur || !cur->properties)
		return (vec(0.0, 0.0, 0.0));
	attr = cur->properties;
	while (attr)
	{
		value = xmlNodeListGetString(cur->doc, attr->children, 1);
		if (ft_strequ((char *)attr->name, "r"))
			col.z = (float)ft_atoi((char *)value) / 100;
		else if (ft_strequ((char *)attr->name, "g"))
			col.y = (float)ft_atoi((char *)value) / 100;
		else if (ft_strequ((char *)attr->name, "b"))
			col.x = (float)ft_atoi((char *)value) / 100;
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
	return (col);
}

cl_float3	parse_rot(xmlNode *cur)
{
	xmlAttr		*attr;
	xmlChar		*value;
	cl_float3	rot;

	if (!cur || !cur->properties)
		return (vec(0.f, 0.f, 0.f));
	attr = cur->properties;
	while (attr)
	{
		value = xmlNodeListGetString(cur->doc, attr->children, 1);
		if (ft_strequ((char *)attr->name, "x"))
			rot.x = ft_atoi((char *)value);
		else if (ft_strequ((char *)attr->name, "y"))
			rot.y = ft_atoi((char *)value);
		else if (ft_strequ((char *)attr->name, "z"))
			rot.z = ft_atoi((char *)value);
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
	return (rot);
}

cl_float3	parse_pos(xmlNode *cur)
{
	xmlAttr		*attr;
	xmlChar		*value;
	cl_float3	pos;

	if (!cur || !cur->properties)
		return (vec(0.f, 0.f, 0.f));
	attr = cur->properties;
	while (attr)
	{
		value = xmlNodeListGetString(cur->doc, attr->children, 1);
		if (ft_strequ((char *)attr->name, "x"))
			pos.x = ft_atoi((char *)value);
		else if (ft_strequ((char *)attr->name, "y"))
			pos.y = ft_atoi((char *)value);
		else if (ft_strequ((char *)attr->name, "z"))
			pos.z = ft_atoi((char *)value);
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
	return (pos);
}
