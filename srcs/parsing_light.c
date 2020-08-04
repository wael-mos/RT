/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <evogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:45:02 by evogel            #+#    #+#             */
/*   Updated: 2020/07/28 15:19:40 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_type		read_type(char *word)
{
	if (ft_strequ(word, "Plane") || ft_strequ(word, "plane"))
		return (PLANE);
	if (ft_strequ(word, "Sphere") || ft_strequ(word, "sphere"))
		return (SPHERE);
	if (ft_strequ(word, "Cylindre") || ft_strequ(word, "cylindre"))
		return (CYLINDER);
	if (ft_strequ(word, "Cylinder") || ft_strequ(word, "cylinder"))
		return (CYLINDER);
	if (ft_strequ(word, "Cone") || ft_strequ(word, "cone"))
		return (CONE);
	if (ft_strequ(word, "Tore") || ft_strequ(word, "tore"))
		return (TORE);
	if (ft_strequ(word, "Disk") || ft_strequ(word, "disk"))
		return (DISK);
	if (ft_strequ(word, "Paraboloid") || ft_strequ(word, "paraboloid"))
		return (PARA);
	if (ft_strequ(word, "cube") || ft_strequ(word, "Cube"))
		return (CUBE);
	return (9);
}

int			parse_objects(xmlNode *node, t_scene *scene)
{
	xmlNode *cur;
	size_t	count;

	if (!node || !node->children)
		return (SUCCESS);
	scene->num_obj = xmlChildElementCount(node);
	cur = node->children;
	count = 0;
	while (cur)
	{
		if (cur->type == XML_ELEMENT_NODE)
			parse_anobj(cur, &scene->objs[count++]);
		cur = cur->next;
	}
	xmlFree(cur);
	return (SUCCESS);
}

static void	parse_alight(xmlNode *node, t_light *light)
{
	xmlNode	*cur;

	if (!node || !node->children)
		return ;
	cur = node->children;
	while (cur)
	{
		if (ft_strequ((char *)cur->name, "pos"))
			light->pos = parse_pos(cur);
		else if (ft_strequ((char *)cur->name, "col"))
			light->col = parse_col(cur);
		cur = cur->next;
	}
	xmlFree(cur);
}

static void	parse_lights_data(xmlNode *node, t_scene *scene)
{
	xmlNode *cur;
	size_t	count;

	cur = node->children;
	count = 0;
	while (cur)
	{
		if (cur->type == XML_ELEMENT_NODE)
			parse_alight(cur, &scene->lights[count++]);
		cur = cur->next;
	}
	xmlFree(cur);
}

int			parse_lights(xmlNode *node, t_scene *scene)
{
	xmlChar	*value;

	if (!node || !node->children)
		return (SUCCESS);
	value = NULL;
	if (node->properties)
	{
		if (ft_strequ((char *)node->properties->name, "ambient"))
		{
			value = xmlNodeListGetString(node->doc,
				node->properties->children, 1);
			scene->ambient = (float)ft_atoi((char *)value) / 100;
			scene->ambient = scene->ambient < 0 ? 0 : scene->ambient;
			xmlFree(value);
		}
	}
	scene->num_light = xmlChildElementCount(node);
	parse_lights_data(node, scene);
	return (SUCCESS);
}
