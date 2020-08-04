/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_perlin_water.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:07:47 by wael-mos          #+#    #+#             */
/*   Updated: 2020/07/20 22:35:59 by wael-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_water			parse_water(xmlNode *cur)
{
	xmlAttr	*attr;
	xmlChar	*value;
	t_water	res;

	res.frequency = 0;
	res.ampli = 0;
	res.mode = 0;
	if (!cur || !cur->properties)
		return (res);
	attr = cur->properties;
	while (attr)
	{
		value = xmlNodeListGetString(cur->doc, attr->children, 1);
		if (ft_strequ((char *)attr->name, "freq"))
			res.frequency = ft_atoi((char *)value);
		else if (ft_strequ((char *)attr->name, "ampli"))
			res.ampli = (float)ft_atoi((char *)value) / 100;
		else if (ft_strequ((char *)attr->name, "mode"))
			res.mode = ft_atoi((char *)value);
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
	return (res);
}

static void		if_forest(t_perlin *res, xmlAttr *attr, xmlChar *value)
{
	if (ft_strequ((char *)attr->name, "octav"))
		res->octav = ft_atoi((char *)value);
	else if (ft_strequ((char *)attr->name, "linex"))
		res->linex = ft_atoi((char *)value);
	else if (ft_strequ((char *)attr->name, "liney"))
		res->liney = ft_atoi((char *)value);
	else if (ft_strequ((char *)attr->name, "ringnb"))
		res->ringnb = ft_atoi((char *)value);
	else if (ft_strequ((char *)attr->name, "turbpow"))
		res->turbpow = (float)ft_atoi((char *)value) / 100;
	else if (ft_strequ((char *)attr->name, "scaler"))
		res->scaler = (float)ft_atoi((char *)value) / 10000;
	else if (ft_strequ((char *)attr->name, "opacity"))
		res->opacity = (float)ft_atoi((char *)value) / 100;
}

static void		parse_perlin_tex(xmlNode *cur, int type, t_perlin *res)
{
	xmlAttr		*attr;
	xmlChar		*value;

	res->type = 0;
	if (!cur || !cur->properties)
		return ;
	attr = cur->properties;
	res->type = type;
	while (attr)
	{
		value = xmlNodeListGetString(cur->doc, attr->children, 1);
		if_forest(res, attr, value);
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
}

t_perlin		parse_perlin(xmlNode *node)
{
	xmlNode		*cur;
	t_perlin	res;

	res.type = 0;
	res.ringnb = 0;
	res.turbpow = 0.f;
	if (!node || !node->children)
		return (res);
	cur = node->children;
	while (cur)
	{
		if (ft_strequ((char *)cur->name, "wood"))
			parse_perlin_tex(cur, 1, &res);
		else if (ft_strequ((char *)cur->name, "marble"))
			parse_perlin_tex(cur, 2, &res);
		else if (ft_strequ((char *)cur->name, "cloud"))
			parse_perlin_tex(cur, 3, &res);
		cur = cur->next;
	}
	xmlFree(cur);
	return (res);
}
