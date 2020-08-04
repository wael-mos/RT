/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporter_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 10:22:48 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/13 10:22:50 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	exporter_campos(xmlTextWriterPtr writer, t_scene *scene)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "pos") < 0)
		return (1);
	if (export_itoa(writer, "x", scene->cam.pos.x))
		return (1);
	if (export_itoa(writer, "y", scene->cam.pos.y))
		return (1);
	if (export_itoa(writer, "z", scene->cam.pos.z))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}

int	exporter_camrot(xmlTextWriterPtr writer, t_scene *scene)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "rot") < 0)
		return (1);
	if (export_itoa(writer, "x", rad2deg(scene->cam.rot.x)))
		return (1);
	if (export_itoa(writer, "y", rad2deg(scene->cam.rot.y)))
		return (1);
	if (export_itoa(writer, "z", rad2deg(scene->cam.rot.z)))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}

int	exporter_camera(xmlTextWriterPtr writer, t_scene *scene)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "camera") < 0)
		return (1);
	if (export_itoa(writer, "fov", scene->cam.fov))
		return (1);
	if (exporter_campos(writer, scene) == 1 || \
	exporter_camrot(writer, scene) == 1)
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}
