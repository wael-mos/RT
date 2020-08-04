/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporter_lights.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 10:22:57 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/13 10:22:58 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	exporter_lightpos(xmlTextWriterPtr writer, t_scene *scene, int i)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "pos") < 0)
		return (1);
	if (export_itoa(writer, "x", scene->lights[i].pos.x))
		return (1);
	if (export_itoa(writer, "y", scene->lights[i].pos.y))
		return (1);
	if (export_itoa(writer, "z", scene->lights[i].pos.z))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}

int	exporter_lightcol(xmlTextWriterPtr writer, t_scene *scene, int i)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "col") < 0)
		return (1);
	if (export_itoa(writer, "r", (scene->lights[i].col.z * 100)))
		return (1);
	if (export_itoa(writer, "g", (scene->lights[i].col.y * 100)))
		return (1);
	if (export_itoa(writer, "b", (scene->lights[i].col.x * 100)))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}

int	exporter_lights(xmlTextWriterPtr writer, t_scene *scene)
{
	int i;

	i = 0;
	if (xmlTextWriterStartElement(writer, BAD_CAST "lights") < 0)
		return (1);
	if (export_itoa(writer, "ambient", (scene->ambient * 100)))
		return (1);
	while (i < scene->num_light)
	{
		if (xmlTextWriterStartElement(writer, BAD_CAST "light") < 0)
			return (1);
		if (exporter_lightpos(writer, scene, i) == 1 || \
				exporter_lightcol(writer, scene, i) == 1)
			return (1);
		if (xmlTextWriterEndElement(writer) < 0)
			return (1);
		++i;
	}
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}
