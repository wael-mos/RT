/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporter_object2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 10:43:52 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/28 15:39:43 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			export_itoa(xmlTextWriterPtr writer, char *name, float data)
{
	char *cdata;

	cdata = ft_itoa((int)data);
	if (xmlTextWriterWriteAttribute(writer, (const xmlChar *)name, \
				(const xmlChar *)cdata))
	{
		free(cdata);
		return (1);
	}
	free(cdata);
	return (0);
}

const char	*exporter_get_objtype(t_obj object)
{
	if (object.type == PLANE)
		return ("plane");
	else if (object.type == SPHERE)
		return ("sphere");
	else if (object.type == CYLINDER)
		return ("cylinder");
	else if (object.type == CONE)
		return ("cone");
	else if (object.type == TORE)
		return ("tore");
	else if (object.type == DISK)
		return ("disk");
	else if (object.type == PARA)
		return ("paraboloid");
	else if (object.type == TORE)
		return ("tore");
	else if (object.type == CUBE)
		return ("cube");
	return (NULL);
}

int			export_objpos(xmlTextWriterPtr writer, t_scene *scene, int i)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "pos") < 0)
		return (1);
	if (export_itoa(writer, "x", scene->objs[i].pos.x))
		return (1);
	if (export_itoa(writer, "y", scene->objs[i].pos.y))
		return (1);
	if (export_itoa(writer, "z", scene->objs[i].pos.z))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	if (xmlTextWriterStartElement(writer, BAD_CAST "height") < 0)
		return (1);
	if (export_itoa(writer, "value", scene->objs[i].height))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}

int			export_objrad(xmlTextWriterPtr writer, t_scene *scene, int i)
{
	if (scene->objs[i].type != CONE)
	{
		if (export_itoa(writer, "radius", scene->objs[i].rad))
			return (1);
	}
	else
	{
		if (export_itoa(writer, "angle", rad2deg(scene->objs[i].rad)))
			return (1);
	}
	return (0);
}
