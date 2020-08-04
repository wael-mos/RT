/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:25:18 by wael-mos          #+#    #+#             */
/*   Updated: 2020/07/29 10:25:22 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	if_forest(int ret, t_scene *scene, xmlNode *cur_node)
{
	if (ft_strequ((char *)cur_node->name, "windows"))
		parse_windows(cur_node, scene);
	else if (ft_strequ((char *)cur_node->name, "effects"))
		parse_effects(cur_node, scene);
	else if (ft_strequ((char *)cur_node->name, "camera"))
		parse_cam(cur_node, scene);
	else if (ft_strequ((char *)cur_node->name, "lights"))
		ret |= parse_lights(cur_node, scene);
	else if (ft_strequ((char *)cur_node->name, "objects"))
		ret |= parse_objects(cur_node, scene);
	return (ret);
}

static int	split_parsing(xmlNode *begin, t_scene *scene)
{
	xmlNode *cur_node;
	int		ret;

	ret = SUCCESS;
	if (!begin)
		return (ret);
	cur_node = begin;
	while (cur_node)
	{
		if (cur_node->type == XML_ELEMENT_NODE)
			ret = if_forest(ret, scene, cur_node);
		cur_node = cur_node->next;
	}
	xmlFree(cur_node);
	return (ret);
}

void		create_oids(t_scene *scene)
{
	int		i;
	char	*str;

	i = 0;
	while (i < scene->num_obj)
	{
		str = ft_itoa(i);
		if (scene->objs[i].type == PLANE)
			scene->objs[i].id = ft_strjoin("Plane | Object #", str);
		else if (scene->objs[i].type == SPHERE)
			scene->objs[i].id = ft_strjoin("Sphere | Object #", str);
		else if (scene->objs[i].type == CYLINDER)
			scene->objs[i].id = ft_strjoin("Cylinder | Object #", str);
		else if (scene->objs[i].type == CONE)
			scene->objs[i].id = ft_strjoin("Cone | Object #", str);
		else if (scene->objs[i].type == TORE)
			scene->objs[i].id = ft_strjoin("Tore | Object #", str);
		else if (scene->objs[i].type == DISK)
			scene->objs[i].id = ft_strjoin("Disk | Object #", str);
		else if (scene->objs[i].type == PARA || scene->objs[i].type == CUBE)
			end_oids(scene, i);
		++i;
		free(str);
	}
}

void		create_lids(t_scene *scene)
{
	int		i;
	char	*str;

	i = 0;
	while (i < scene->num_light)
	{
		str = ft_itoa(i);
		scene->lights[i].id = ft_strjoin("Light #", str);
		++i;
		free(str);
	}
}

int			parsing(char *av, t_scene *scene)
{
	xmlDoc	*document;
	xmlNode	*root;
	int		ret;

	ret = SUCCESS;
	if ((document = xmlReadFile(av, NULL, 0)) == NULL)
		return (FAILURE);
	root = xmlDocGetRootElement(document);
	ret = split_parsing(root->children, scene);
	xmlFreeDoc(document);
	xmlCleanupParser();
	create_lids(scene);
	create_oids(scene);
	check_value(scene);
	return (ret);
}
