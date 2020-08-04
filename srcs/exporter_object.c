/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporter_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 10:23:01 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/13 10:30:26 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			export_objprop(xmlTextWriterPtr writer, t_scene *scene, int i)
{
	if (export_objrad(writer, scene, i))
		return (1);
	if (export_itoa(writer, "reflect", (scene->objs[i].refl * 100)))
		return (1);
	if (export_itoa(writer, "refract", (scene->objs[i].refr * 100)))
		return (1);
	if (export_itoa(writer, "ior", (scene->objs[i].ior * 100)))
		return (1);
	if (export_itoa(writer, "shine", scene->objs[i].shine))
		return (1);
	if (export_itoa(writer, "inf", (scene->objs[i].inf + 1)))
		return (1);
	return (0);
}

int			export_objrot(xmlTextWriterPtr writer, t_scene *scene, int i)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "rot") < 0)
		return (1);
	if (export_itoa(writer, "x", rad2deg(scene->objs[i].rot.x)))
		return (1);
	if (export_itoa(writer, "y", rad2deg(scene->objs[i].rot.y)))
		return (1);
	if (export_itoa(writer, "z", rad2deg(scene->objs[i].rot.z)))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}

int			export_objcol(xmlTextWriterPtr writer, t_scene *scene, int i)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "col") < 0)
		return (1);
	if (export_itoa(writer, "r", (scene->objs[i].col.z * 100)))
		return (1);
	if (export_itoa(writer, "g", (scene->objs[i].col.y * 100)))
		return (1);
	if (export_itoa(writer, "b", (scene->objs[i].col.x * 100)))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}

int			export_objchecker(xmlTextWriterPtr writer, t_scene *scene, int i)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "checkerboard") < 0)
		return (1);
	if (export_itoa(writer, "height", (scene->objs[i].checkh)))
		return (1);
	if (export_itoa(writer, "width", (scene->objs[i].checkw)))
		return (1);
	if (export_itoa(writer, "r", (scene->objs[i].checkcol.z * 100)))
		return (1);
	if (export_itoa(writer, "g", (scene->objs[i].checkcol.y * 100)))
		return (1);
	if (export_itoa(writer, "b", (scene->objs[i].checkcol.x * 100)))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}

int			exporter_objects(xmlTextWriterPtr writer, t_scene *scene)
{
	int i;

	i = 0;
	if (xmlTextWriterStartElement(writer, BAD_CAST "objects") < 0)
		return (1);
	while (i < scene->num_obj)
	{
		if (xmlTextWriterStartElement(writer, \
		(const xmlChar *)exporter_get_objtype(scene->objs[i])) < 0)
			return (1);
		if (export_objprop(writer, scene, i) == 1 || \
		export_perlin(writer, scene, i) == 1 || \
		export_water(writer, scene, i) == 1 || \
		export_objpos(writer, scene, i) == 1 || \
		export_objrot(writer, scene, i) == 1 || \
		export_objcol(writer, scene, i) == 1 || \
		export_objchecker(writer, scene, i) == 1)
			return (1);
		if (xmlTextWriterEndElement(writer) < 0)
			return (1);
		++i;
	}
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}
