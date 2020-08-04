/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_rot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:59:55 by evogel            #+#    #+#             */
/*   Updated: 2020/07/13 13:58:22 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3			rotate_x(cl_float3 v, double theta)
{
	cl_float3	res;
	float		cos_t;
	float		sin_t;

	cos_t = cos(theta);
	sin_t = sin(theta);
	res.x = dot(v, vec(1, 0, 0));
	res.y = dot(v, vec(0, cos_t, -sin_t));
	res.z = dot(v, vec(0, sin_t, cos_t));
	return (res);
}

cl_float3			rotate_y(cl_float3 v, double theta)
{
	cl_float3	res;
	float		cos_t;
	float		sin_t;

	cos_t = cos(theta);
	sin_t = sin(theta);
	res.x = dot(v, vec(cos_t, 0, sin_t));
	res.y = dot(v, vec(0, 1, 0));
	res.z = dot(v, vec(-sin_t, 0, cos_t));
	return (res);
}

cl_float3			rotate_z(cl_float3 v, double theta)
{
	cl_float3	res;
	float		cos_t;
	float		sin_t;

	cos_t = cos(theta);
	sin_t = sin(theta);
	res.x = dot(v, vec(cos_t, -sin_t, 0));
	res.y = dot(v, vec(sin_t, cos_t, 0));
	res.z = dot(v, vec(0, 0, 1));
	return (res);
}

cl_float3			rotate_full(cl_float3 ori, cl_float3 rot)
{
	cl_float3	res;

	res = ori;
	res = rotate_z(res, rot.z);
	res = rotate_x(res, rot.x);
	res = rotate_y(res, rot.y);
	return (res);
}
