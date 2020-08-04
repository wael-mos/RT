/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:02:09 by evogel            #+#    #+#             */
/*   Updated: 2020/07/29 10:38:42 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_checkerboard(xmlNode *cur, t_obj *obj)
{
	xmlAttr		*attr;
	xmlChar		*value;

	if (!cur || !cur->properties)
		return ;
	attr = cur->properties;
	while (attr)
	{
		value = xmlNodeListGetString(cur->doc, attr->children, 1);
		if (ft_strequ((char *)attr->name, "r"))
			obj->checkcol.z = (float)ft_atoi((char *)value) / 100;
		else if (ft_strequ((char *)attr->name, "g"))
			obj->checkcol.y = (float)ft_atoi((char *)value) / 100;
		else if (ft_strequ((char *)attr->name, "b"))
			obj->checkcol.x = (float)ft_atoi((char *)value) / 100;
		else if (ft_strequ((char *)attr->name, "height"))
			obj->checkh = ft_atoi((char *)value);
		else if (ft_strequ((char *)attr->name, "width"))
			obj->checkw = ft_atoi((char *)value);
		else if (ft_strequ((char *)attr->name, "value"))
			obj->height = ft_atoi((char *)value);
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
}

static void	parse_anobj_data(xmlNode *cur, t_obj *obj)
{
	while (cur)
	{
		if (ft_strequ((char *)cur->name, "pos"))
			obj->pos = parse_pos(cur);
		else if (ft_strequ((char *)cur->name, "rot"))
		{
			obj->rot = deg(parse_pos(cur));
			obj->axe = get_axe(obj->rot);
		}
		else if (ft_strequ((char *)cur->name, "col"))
			obj->col = parse_col(cur);
		else if (ft_strequ((char *)cur->name, "water"))
			obj->water = parse_water(cur);
		else if (ft_strequ((char *)cur->name, "perlin"))
			obj->perlin = parse_perlin(cur);
		else if (ft_strequ((char *)cur->name, "checkerboard"))
			parse_checkerboard(cur, obj);
		else if (ft_strequ((char *)cur->name, "height"))
			parse_checkerboard(cur, obj);
		cur = cur->next;
	}
	xmlFree(cur);
}

static void	if_forest(t_obj *obj, xmlAttr *attr, xmlChar *value)
{
	if (ft_strequ((char *)attr->name, "radius"))
		obj->rad = ft_atoi((char *)value);
	if (ft_strequ((char *)attr->name, "angle"))
		obj->rad = ft_atoi((char *)value) * M_PI / 180;
	if (ft_strequ((char *)attr->name, "shine"))
		obj->shine = ft_atoi((char *)value);
	if (ft_strequ((char *)attr->name, "ior"))
		obj->ior = (float)ft_atoi((char *)value) / 100;
	if (ft_strequ((char *)attr->name, "reflect"))
		obj->refl = (float)ft_atoi((char *)value) / 100;
	if (ft_strequ((char *)attr->name, "refract"))
		obj->refr = (float)ft_atoi((char *)value) / 100;
	if (ft_strequ((char *)attr->name, "inf"))
		obj->inf = ft_atoi((char *)value);
}

void		parse_anobj(xmlNode *node, t_obj *obj)
{
	xmlNode	*cur;
	xmlAttr	*attr;
	xmlChar	*value;

	if (!node || !node->children)
		return ;
	cur = node->children;
	obj->type = read_type((char *)node->name);
	attr = node->properties;
	while (attr)
	{
		value = xmlNodeListGetString(node->doc, attr->children, 1);
		if_forest(obj, attr, value);
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
	parse_anobj_data(cur, obj);
	obj->inf = (!obj->inf) ? 2 : obj->inf;
	obj->inf -= 1;
	obj->height = (!obj->height) ? 300 : obj->height;
}

void		end_oids(t_scene *scene, int i)
{
	char *str;

	str = ft_itoa(i);
	if (scene->objs[i].type == PARA)
		scene->objs[i].id = ft_strjoin("Paraboloid | Object #", str);
	else if (scene->objs[i].type == CUBE)
		scene->objs[i].id = ft_strjoin("Goursat | Object #", str);
	free(str);
}
