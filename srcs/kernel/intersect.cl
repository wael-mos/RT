float3	get_phit_normal(t_ray *r, float3 p_hit, __global t_obj *obj, float t)
{
	float3	n_hit;
	float3 	tmp;
	float 	tmp2;
	float 	tmp3;

	n_hit = (float3)(0, 1.f, 0);
	if (obj->type == PLANE || obj->type == DISK)
	{
		if (obj->water.mode)
			n_hit = normal_perturb_water(p_hit, obj->water.frequency, obj->water.ampli, obj->water.mode);
		else
			n_hit = -1 * obj->axe;
	}
	else if (obj->type == SPHERE)
		n_hit = normalize(p_hit - obj->pos);
	else if (obj->type == CYLINDER)
	{
		tmp2 = dot(r->dir, obj->axe) * t + dot(r->ori - obj->pos, obj->axe);
		n_hit = normalize(p_hit - obj->pos - obj->axe * tmp2);
	}
	else if (obj->type == CONE)
	{
		tmp2 = dot(r->dir, obj->axe) * t + dot(r->ori - obj->pos, obj->axe);
		tmp3 = tan(obj->rad / 2);
		n_hit = normalize(p_hit - obj->pos - (1 + tmp3 * tmp3) * obj->axe * tmp2);
	}
	else if (obj->type == TORE)
	{
		float one = ((p_hit.x * p_hit.x) + (p_hit.y * p_hit.y) + (p_hit.z * p_hit.z) + (obj->height * obj->height) - (obj->rad * obj->rad));
		n_hit.x = 4.0f * one * p_hit.x;
		n_hit.y = 4.0f * p_hit.y * (one + 2 * (obj->height * obj->height));
		n_hit.z = 4.0f * one * p_hit.z;
		n_hit = normalize(n_hit);
	}
	else if (obj->type == PARA)
	{
		tmp = dot((p_hit - obj->pos), obj->axe);
		n_hit = normalize(p_hit - obj->pos - obj->axe * (tmp + obj->rad));
	}
	else if (obj->type == CUBE)
	{
		n_hit.x = 4.0f * pow(p_hit.x, 3.0f) - 10.0f * p_hit.x;
		n_hit.y = 4.0f * pow(p_hit.y, 3.0f) - 10.0f * p_hit.y;
		n_hit.z = 4.0f * pow(p_hit.z, 3.0f) - 10.0f * p_hit.z;
		n_hit = normalize(n_hit);
	}
	return (n_hit);
}

int			infinite_solver(float a, float b, float c, float *t)
{
	float	t0;
	float	t1;
	float	discr;

	discr = sqrt(b * b - 4 * a * c);
	if (discr < 0.0f)
		return (0);
	else
	{
		t0 = (-b + discr) / (2 * a);
		t1 = (-b - discr) / (2 * a);
		if (t0 > t1)
			t0 = t1;
		if ((t0 > 0.0f) && (t0 < *t))
		{
			*t = t0;
			return (1);
		}
	}
	return (0);
}

int			finite_solver(float a, float b, float c, float *t, __global t_obj *s, t_ray *r)
{
	float	t0;
	float	t1;
	float	discr;
	float m1;
	float m2;

	discr = sqrt(b * b - 4 * a * c);
	if (discr < 0.0f)
		return (0);
	else
	{
		t0 = (-b + discr) / (2 * a);
		t1 = (-b - discr) / (2 * a);
	}
	m1 = dot(r->dir, s->axe) * t0 + dot(r->ori - s->pos, s->axe);
	m2 = dot(r->dir, s->axe) * t1 + dot(r->ori - s->pos, s->axe);
	if ((m1 < s->height || m2 < s->height) && (m1 > 0 || m2 > 0))
	{
		if (m1 < s->height && m1 > 0 && t0 < t1)
		{
			if ((t0 > 0.0f) && (t0 < *t))
			{
				*t = t0;
				return (1);
			}
		}
		else if (m2 < s->height && m2 > 0 && t1 < t0)
		{
			if ((t1 > 0.0f) && (t1 < *t))
			{
				*t = t1;
				return (1);
			}
		}
	}
	return (0);
}

int			cylinder_intersect(t_ray *r, __global t_obj *s, float *t)
{
	float3 dist;
	float a;
	float b;
	float c;

	dist = r->ori - s->pos;
	a = dot(r->dir, r->dir) - dot(r->dir, s->axe) * dot(r->dir, s->axe);
	b = dot(r->dir, dist) - dot(r->dir, s->axe) * dot(dist, s->axe);
	b *= 2;
	c = dot(dist, dist) - dot(dist, s->axe) * dot(dist, s->axe) - s->rad * s->rad;

	if (s->inf == 1)
		return (infinite_solver(a, b, c, t));
	else
		return (finite_solver(a, b, c, t, s, r));
}

int			sphere_intersect(t_ray *r, __global t_obj *s, float *t)
{
	float3	dist;
	float	a;
	float	b;
	float	c;

	dist = r->ori - s->pos;
	a = dot(r->dir, r->dir);
	b = 2.f * dot(r->dir, dist);
	c = dot(dist, dist) - (s->rad * s->rad);
	return (infinite_solver(a, b, c, t));
}

int			plane_intersect(t_ray *r, __global t_obj *s, float *t)
{
	float	a;
	float	b;
	float	t0;

	a = dot(s->pos - r->ori, s->axe);
	b = dot(r->dir, s->axe);
	if (b < 0.0f)
		return (0);
	else
	{
		t0 = a / b;
		if (t0 > 0.0f && t0 < *t)
		{
			*t = t0;
			return (1);
		}
	}
	return (0);
}

int			plane_shadow(t_ray *r, __global t_obj *s, float *t)
{
	float	a;
	float	b;
	float	t0;
	t_obj tmp;

	tmp = (*s);
	tmp.axe *= -1;
	a = dot(s->pos - r->ori, tmp.axe);
	b = dot(r->dir, tmp.axe);
	if (b < 0.0f)
		return (0);
	else
	{
		t0 = a / b;
		if (t0 > 0.0f && t0 < *t)
		{
			*t = t0;
			return (1);
		}
	}
	return (0);
}

int			cone_intersect(t_ray *r, __global t_obj *s, float *t)
{
	float k;
	float a;
	float b;
	float c;
	float3 dist;

	k = tan(s->rad/2);
	dist = r->ori - s->pos;
	a = dot(r->dir, r->dir) - (1 + k * k) * dot(r->dir, s->axe) * dot(r->dir, s->axe);
	b = dot(r->dir, dist) - (1 + k * k) * dot(r->dir, s->axe) * dot(dist, s->axe);
	b *= 2;
	c = dot(dist, dist) - (1 + k * k) * dot(dist, s->axe) * dot(dist, s->axe);

	if (s->inf == 1)
		return (infinite_solver(a, b, c, t));
	else
		return (finite_solver(a, b, c, t, s, r));
}

int			paraboloid_intersect(t_ray *r, __global t_obj *s, float *t)
{
	float3 x;
	float  a;
	float  b;
	float  c;

	x = r->ori - s->pos;
	a = dot(r->dir, r->dir) - dot(r->dir, s->axe) * dot(r->dir, s->axe);
	b = 2 * (dot(r->dir, x) - dot(r->dir, s->axe) * (dot(x, s->axe) + 2 * s->rad));
	c = dot(x, x) - dot(x, s->axe) * (dot(x, s->axe) + 4 * s->rad);
	if (s->inf == 1)
		return (infinite_solver(a, b, c, t));
	else
		return (finite_solver(a, b, c, t, s, r));
}

int			disk_intersect(t_ray *r, __global t_obj *s, float *t)
{
	float3	dist;
	float3	p_hit;
	float 	d2;
	float		t0 = FLT_MAX;

	if (plane_intersect(r, s, &t0) == 1)
	{
		p_hit = r->ori + r->dir * t0;
		dist = p_hit - s->pos;
		d2 = fabs(dot(dist, dist));
		if (d2 <= (s->rad * s->rad) && t0 < (*t))
		{
			*t = t0;
			return (1);
		}
	}
	return (0);
}

int 	disk_shadow(t_ray *r, __global t_obj *s, float *t)
{
	float	a;
	float	b;
	float	t0;
	t_obj 	tmp;
	float3  dist;
	float3	p_hit;
	float 	d2;

	tmp = (*s);
	tmp.axe *= -1;
	a = dot(tmp.pos - r->ori, tmp.axe);
	b = dot(r->dir, tmp.axe);
	if (b < 0.0f)
		return (0);
	else
	{
		t0 = a / b;
		if (t0 > 0.0f && t0 < *t)
		{
			p_hit = r->ori + r->dir * t0;
			dist = p_hit - s->pos;
			d2 = fabs(dot(dist, dist));
			if (d2 <= (s->rad * s->rad))
			{
				*t = t0;
				return (1);
			}
		}
	}
	return (0);
}

int			tore_intersect(t_ray *r, __global t_obj *s, float *t)
{
	double		c[5];
	double		div;
	double3		k;
	double e;

	k.x = r->dir.x * r->dir.x + r->dir.y * r->dir.y + r->dir.z * r->dir.z;
	k.y = 4.0f * s->height * s->height;
	k.z = (r->ori.x - s->pos.x) * r->dir.x + (r->ori.y - s->pos.y) * r->dir.y +\
		(r->ori.z - s->pos.z) * r->dir.z;

	e = (r->ori.x - s->pos.x) * (r->ori.x - s->pos.x) + (r->ori.y - s->pos.y) *\
		(r->ori.y - s->pos.y) + (r->ori.z - s->pos.z) * (r->ori.z - s->pos.z) -\
			s->height * s->height - s->rad * s->rad;

	c[0] = e * e - k.y * (s->rad * s->rad - (r->ori.y - s->pos.y) * (r->ori.y - s->pos.y));
	c[1] = 4.0f * k.z * e + 2.0f * k.y * (r->ori.y - s->pos.y)* r->dir.y;
	c[2] = 2.0f * k.x * e + 4.0f * k.z * k.z + k.y * r->dir.y * r->dir.y;
	c[3] = 4.0f * k.x * k.z;
	c[4] = k.x * k.x;
	double4 res;
  if (ft_solve_4(c, &res))
	{
		double  tmpt = res.x;
		tmpt = min(tmpt, res.y);
		tmpt = min(tmpt, res.z);
		tmpt = min(tmpt, res.w);
		if (tmpt < *t)
		{
			*t = tmpt;
			return (1);
		}
	}
	return (0);
}

int			cube_intersect(t_ray *r, __global t_obj *s, float *t)
{
	double		c[5];
	double3		origin;

	origin.x = (double)r->ori.x - (double)s->pos.x;
	origin.y = (double)r->ori.y - (double)s->pos.y;
	origin.z = (double)r->ori.z - (double)s->pos.z;

	c[0] = pow(origin.x, 4) + pow(origin.y, 4) + pow(origin.z, 4) - 5.0 * (pow(origin.x, 2) + pow(origin.y, 2) + pow(origin.z, 2)) + s->rad;
	c[1] = 4.0 * ( pow(origin.x, 3) * r->dir.x + pow(origin.y, 3) * r->dir.y + pow(origin.z, 3) * r->dir.z ) - 10. * (r->dir.x * origin.x + r->dir.y * origin.y + r->dir.z * origin.z);
	c[2] = c[2] = 6.0 * ( pow(r->dir.x, 2) * pow(origin.x, 2) + pow(r->dir.y, 2) * pow(origin.y, 2) + pow(r->dir.z, 2) * pow(origin.z, 2) )	- 5.0 * ( pow(r->dir.x, 2) + pow(r->dir.y, 2) + pow(r->dir.z, 2) );
	c[3] = 4.0 * ( pow(r->dir.x, 3) * origin.x + pow(r->dir.y, 3) * origin.y + pow(r->dir.z, 3) * origin.z );
	c[4] = pow(r->dir.x, 4) + pow(r->dir.y, 4) + pow(r->dir.z, 4);
	double4 res;
  if (ft_solve_4(c, &res))
	{
		double  tmpt = res.x;
		tmpt = min(tmpt, res.y);
		tmpt = min(tmpt, res.z);
		tmpt = min(tmpt, res.w);
		if (tmpt < *t)
		{
			*t = tmpt;
			return (1);
		}
	}
	return (0);
}

__global t_obj	*get_obj_intersect(__global t_scene *scene, t_ray *ray, float *t)
{
	__global t_obj	*curr_obj;
	int				closest;
	int				i;

	closest = -1;
	i = 0;
	while (i < scene->num_obj)
	{
		curr_obj = &scene->objs[i];
		if (curr_obj->type == PLANE && plane_intersect(ray, curr_obj, t))
			closest = i;
		if (curr_obj->type == SPHERE && sphere_intersect(ray, curr_obj, t))
			closest = i;
		if (curr_obj->type == CYLINDER && cylinder_intersect(ray, curr_obj, t))
			closest = i;
		if (curr_obj->type == CONE && cone_intersect(ray, curr_obj, t))
			closest = i;
		if (curr_obj->type == TORE && tore_intersect(ray, curr_obj, t))
			closest = i;
		if (curr_obj->type == DISK && disk_intersect(ray, curr_obj, t))
			closest = i;
		if (curr_obj->type == PARA && paraboloid_intersect(ray, curr_obj, t))
			closest = i;
		if (curr_obj->type == CUBE && cube_intersect(ray, curr_obj, t))
			closest = i;
		++i;
	}
	if (closest == -1)
		return (0);
	return (&scene->objs[closest]);
}

__global t_obj	*get_shadow_intersect(__global t_scene *scene, t_ray *ray, float *t)
{
	__global t_obj	*curr_obj;
	int				closest;
	int				i;

	closest = -1;
	i = 0;
	while (i < scene->num_obj)
	{
		curr_obj = &scene->objs[i];
		if (curr_obj->type == PLANE && plane_shadow(ray, curr_obj, t))
			closest = i;
		if (curr_obj->type == SPHERE && sphere_intersect(ray, curr_obj, t))
			closest = i;
		if (curr_obj->type == CYLINDER && cylinder_intersect(ray, curr_obj, t))
			closest = i;
		if (curr_obj->type == CONE && cone_intersect(ray, curr_obj, t))
			closest = i;
		if (curr_obj->type == TORE && tore_intersect(ray, curr_obj, t))
			closest = i;
		if (curr_obj->type == DISK && disk_shadow(ray, curr_obj, t))
			closest = i;
		if (curr_obj->type == PARA && paraboloid_intersect(ray, curr_obj, t))
			closest = i;
		if (curr_obj->type == CUBE && cube_intersect(ray, curr_obj, t))
			closest = i;
		++i;
	}
	if (closest == -1)
		return (0);
	return (&scene->objs[closest]);
}
