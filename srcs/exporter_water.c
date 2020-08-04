/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporter_water.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 10:23:10 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/13 10:49:26 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	export_water(xmlTextWriterPtr writer, t_scene *scene, int i)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "water") < 0)
		return (1);
	if (export_itoa(writer, "freq", scene->objs[i].water.frequency))
		return (1);
	if (export_itoa(writer, "ampli", (scene->objs[i].water.ampli * 100)))
		return (1);
	if (export_itoa(writer, "mode", scene->objs[i].water.mode))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}

int	export_effects2(xmlTextWriterPtr writer, t_scene *scene)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "saturation") < 0)
		return (1);
	if (export_itoa(writer, "value", (scene->saturation * 10)))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	if (xmlTextWriterStartElement(writer, BAD_CAST "gamma") < 0)
		return (1);
	if (export_itoa(writer, "value", (scene->gamma * 10)))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}

int	export_effects(xmlTextWriterPtr writer, t_scene *scene)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "effects") < 0)
		return (1);
	if (xmlTextWriterStartElement(writer, BAD_CAST "filter") < 0)
		return (1);
	if (export_itoa(writer, "type", scene->effect))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	if (xmlTextWriterStartElement(writer, BAD_CAST "background") < 0)
		return (1);
	if (export_itoa(writer, "r", (scene->bg.z * 100)))
		return (1);
	if (export_itoa(writer, "g", (scene->bg.y * 100)))
		return (1);
	if (export_itoa(writer, "b", (scene->bg.x * 100)))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	if (export_effects2(writer, scene))
		return (1);
	return (0);
}
