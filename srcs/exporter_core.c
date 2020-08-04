/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporter_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoquel <achoquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 10:22:35 by achoquel          #+#    #+#             */
/*   Updated: 2020/07/13 10:22:44 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		exporter_basic(xmlTextWriterPtr writer, t_scene *scene)
{
	if (xmlTextWriterStartElement(writer, BAD_CAST "scene") < 0)
		return (1);
	if (xmlTextWriterStartElement(writer, BAD_CAST "windows") < 0)
		return (1);
	if (xmlTextWriterStartElement(writer, BAD_CAST "size") < 0)
		return (1);
	if (xmlTextWriterWriteAttribute(writer, BAD_CAST "x", BAD_CAST "1445"))
		return (1);
	if (xmlTextWriterWriteAttribute(writer, BAD_CAST "y", BAD_CAST "1008"))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	if (xmlTextWriterStartElement(writer, BAD_CAST "bouncenb") < 0)
		return (1);
	if (export_itoa(writer, "value", scene->bouncenb))
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	if (xmlTextWriterEndElement(writer) < 0)
		return (1);
	return (0);
}

char	*exporter_make_filename(int n)
{
	char		*filename;

	if (!(filename = ft_strnew(26)))
		return (NULL);
	ft_strcat(filename, "./scenes/saved_scene");
	filename[20] = n / 10 + '0';
	filename[21] = n % 10 + '0';
	ft_strcat(filename, ".xml");
	return (filename);
}

void	exporter_createxml(xmlBufferPtr buf)
{
	int		n;
	int		fd;
	char	*filename;

	n = 1;
	while (n < 100)
	{
		if (!(filename = exporter_make_filename(n)))
			return (ft_putendl("Error creating file"));
		if ((fd = open(filename, O_CREAT | O_WRONLY | O_EXCL, 0666)) != -1)
			break ;
		free(filename);
		++n;
	}
	if (n == 100)
		return (ft_putendl("Saved scenes limit reached"));
	write(fd, (const char *)buf->content, buf->use);
	ft_printf("%s was successfully created\n", filename);
	free(filename);
	close(fd);
}

int		exporter_main(t_scene *scene)
{
	int					err;
	xmlTextWriterPtr	writer;
	xmlBufferPtr		buf;

	err = 0;
	if (((buf = xmlBufferCreate()) == NULL) || \
			((writer = xmlNewTextWriterMemory(buf, 0)) == NULL) || \
			(xmlTextWriterStartDocument(writer, NULL, MY_ENCODING, NULL) < 0))
		return (1);
	if ((err = exporter_basic(writer, scene) + exporter_camera(writer, scene) +\
		exporter_lights(writer, scene) + exporter_objects(writer, scene) + \
		export_effects(writer, scene)))
		printf("Something wrong happened while saving your file\n");
	if (xmlTextWriterEndDocument(writer) < 0)
		return (1);
	xmlFreeTextWriter(writer);
	if (err != 0)
	{
		xmlBufferFree(buf);
		return (1);
	}
	else
		exporter_createxml(buf);
	xmlBufferFree(buf);
	return (0);
}
