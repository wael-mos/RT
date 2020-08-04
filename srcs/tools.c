/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:51:38 by evogel            #+#    #+#             */
/*   Updated: 2020/07/13 13:58:03 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3	vec(float x, float y, float z)
{
	cl_float3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

float		dot(cl_float3 v1, cl_float3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

cl_float3	normalize(cl_float3 v)
{
	cl_float3	res;
	float		mag;

	res = v;
	mag = sqrt(dot(v, v));
	if (mag > 0)
	{
		mag = 1 / mag;
		res.x *= mag;
		res.y *= mag;
		res.z *= mag;
	}
	return (res);
}

cl_float3	deg(cl_float3 rot)
{
	cl_float3	res;

	res.x = rot.x * M_PI / 180.f;
	res.y = rot.y * M_PI / 180.f;
	res.z = rot.z * M_PI / 180.f;
	return (res);
}

cl_float3	get_axe(cl_float3 rot)
{
	cl_float3 axe;

	axe = vec(0, -1, 0);
	axe = rotate_full(axe, rot);
	return (normalize(axe));
}
