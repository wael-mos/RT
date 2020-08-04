/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporter_perlin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 10:23:05 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/13 10:24:25 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	export_perlin_wood(xmlTextWriterPtr writer, t_scene *scene, int i)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "wood") < 0)
		return (1);
	if (export_itoa(writer, "turbpow", (scene->objs[i].perlin.turbpow * 100)))
		return (1);
	if (export_itoa(writer, "ringnb", (scene->objs[i].perlin.ringnb)))
		return (1);
	if (export_itoa(writer, "scaler", (scene->objs[i].perlin.scaler * 10000)))
		return (1);
	if (export_itoa(writer, "octav", (scene->objs[i].perlin.octav)))
		return (1);
	if (export_itoa(writer, "opacity", (scene->objs[i].perlin.opacity * 100)))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}

int	export_perlin_marble(xmlTextWriterPtr writer, t_scene *scene, int i)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "marble") < 0)
		return (1);
	if (export_itoa(writer, "turbpow", (scene->objs[i].perlin.turbpow * 100)))
		return (1);
	if (export_itoa(writer, "linex", (scene->objs[i].perlin.linex)))
		return (1);
	if (export_itoa(writer, "liney", (scene->objs[i].perlin.liney)))
		return (1);
	if (export_itoa(writer, "scaler", (scene->objs[i].perlin.scaler * 10000)))
		return (1);
	if (export_itoa(writer, "octav", (scene->objs[i].perlin.octav)))
		return (1);
	if (export_itoa(writer, "opacity", (scene->objs[i].perlin.opacity * 100)))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}

int	export_perlin_cloud(xmlTextWriterPtr writer, t_scene *scene, int i)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "cloud") < 0)
		return (1);
	if (export_itoa(writer, "scaler", (scene->objs[i].perlin.scaler * 10000)))
		return (1);
	if (export_itoa(writer, "octav", (scene->objs[i].perlin.octav)))
		return (1);
	if (export_itoa(writer, "opacity", (scene->objs[i].perlin.opacity * 100)))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}

int	export_perlin(xmlTextWriterPtr writer, t_scene *scene, int i)
{
	int err;

	err = 0;
	if (xmlTextWriterStartElement(writer, BAD_CAST "perlin") < 0)
		return (1);
	if (scene->objs[i].perlin.type == 1)
		err = export_perlin_wood(writer, scene, i);
	else if (scene->objs[i].perlin.type == 2)
		err = export_perlin_marble(writer, scene, i);
	else if (scene->objs[i].perlin.type == 3)
		err = export_perlin_cloud(writer, scene, i);
	if (err == 1)
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}
