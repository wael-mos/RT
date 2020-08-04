void  	sphere_mapping(float *u, float *v, float3 *p_hit, float rad)
{
	float theta;
	float phi;
	float rawu;

	theta = atan2(p_hit->x, p_hit->z);
	phi = acos(p_hit->y / rad);
	rawu = theta / (2 * M_PI);
	*u = 1 - (rawu + 0.5);
	*v = 1 - phi / M_PI;
}

void 		cylinder_mapping(float *u, float *v, float3 *p_hit, __global t_obj *obj)
{
	*u = 0;
	*v = p_hit->y / obj->height;
}

int 			reverse_parity(int parity)
{
	if (parity == 1)
		return (0);
	if (parity == 0)
		return (1);
	return (0);
}

float3 		plane_checker(float3 *p_hit, __global t_obj *obj)
{
	int3 cp;
	int3 parity;

	cp.x = (int) (p_hit->x / obj->checkh);
	cp.y = (int) (p_hit->y / obj->checkh);
	cp.z = (int) (p_hit->z / obj->checkh);

	parity.x = ((abs(cp.x) % 2)) == 0 ? 1 : 0;
	parity.y = ((abs(cp.y) % 2)) == 0 ? 1 : 0;
	parity.z = ((abs(cp.z) % 2)) == 0 ? 1 : 0;

	if ((int)p_hit->x < 0)
		parity.x = reverse_parity(parity.x);
	if ((int)p_hit->y < 0)
		parity.y = reverse_parity(parity.y);
	if ((int)p_hit->z < 0)
		parity.z = reverse_parity(parity.z);

	if (parity.z)
	{
		if ((parity.x && parity.y) || (!parity.x && !parity.y))
			return (obj->col);
		return (obj->checkcol);
	}
	else
	{
		if ((parity.x && parity.y) || (!parity.x && !parity.y))
			return (obj->checkcol);
		return (obj->col);
	}
}

float3	get_pattern_col(__global t_obj *obj, float u, float v)
{
	float u2;
	float v2;

	u2 = floor(u * obj->checkw);
	v2 = floor(v * obj->checkh);
	if (fmod((u2 + v2), 2))
		return (obj->col);
	else
		return (obj->checkcol);
}

float3  get_checkerboard_color(__global t_obj *obj, t_ray *p_hit)
{
	float u;
	float v;
	float3 hit;

	u = 0;
	v = 0;
	hit = p_hit->ori - obj->pos;
	if (obj->type == SPHERE)
	{
		sphere_mapping(&u, &v, &hit, obj->rad);
		return (get_pattern_col(obj, u, v));
	}
	else if (obj->type == PLANE || obj->type == DISK)
		return (plane_checker(&hit, obj));
	else if (obj->type == CYLINDER || obj->type == CONE)
	{
		cylinder_mapping(&u, &v, &hit, obj);
		return (get_pattern_col(obj, u, v));
	}
	else
		return (obj->col);
}

float   fresnel(float3 i, float3 n, float ior)
{
	float	kr;
	float	cosi;
	float	cost;
	float	sint;
	float	etai;
	float	etat;

	cosi = ft_clamp(dot(i, n), -1, 1);
	etat = (cosi > 0) ? 1 : ior;
	etai = (cosi > 0) ? ior : 1;
	sint = etai / etat * sqrt(fmax(0.f, 1.f - cosi * cosi));
	kr = 1;
	if (sint < 1)
	{
		cost = sqrt(fmax(0.f, 1.f - sint * sint));
		cosi = fabs(cosi);
		sint = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		kr = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		kr = (sint * sint + kr * kr) / 2.f;
	}
	return (kr);
}

float3   refract(float3 i, float3 normal, float ior)
{
	float	cosi;
	float	k;

	cosi = ft_clamp(dot(i, normal), -1, 1);
	ior = (cosi < 0) ? 1.f / ior : ior / 1.f;
	normal = (cosi >= 0) ? -1.0f * normal : normal;
	cosi *= (cosi < 0) ? -1.f : 1.f;
	k = (1.f - ior * ior * (1.f - cosi * cosi));
	return ((k < 0) ? (float3)(0.f) : ior * i + (ior * cosi - sqrt(k)) * normal);
}

float3	reflect(float3 i, float3 normal)
{
	float	reflect;
	float3	tmp;

	reflect = 2.0f * dot(normal, i);
	tmp = reflect * normal;
	return (i - tmp);
}

float	shine(t_light *light, t_ray n_hit, t_ray *ray, int size)
{
	float3	l_dir;
	float	res;

	l_dir = normalize(n_hit.ori - light->pos);
	l_dir = reflect(-1 * l_dir, n_hit.dir);
	res = pow(fmax(dot(l_dir, normalize(ray->dir)), 0.0f), size);
	return (res < 0.0f ? 0.0f : res);
}

float3		lights2(__global t_scene *scene, float3 mat, t_ray n_hit, t_ray *ray, __global t_obj *curr_obj)
{
	int		i;
	float	k;
	float	d = 0.f;
	float3	col = (float3)(0.f);
	t_ray				light_ray;
	t_light				light;
	__global t_obj		*shade_obj;
	__global t_obj		*tmp;

	tmp = curr_obj;
	i = 0;
	while (i < scene->num_light)
	{
		light = scene->lights[i];
		light_ray.ori = n_hit.ori + 0.02f * n_hit.dir;
		light_ray.dir = normalize(light.pos - light_ray.ori);
		k = 1.f;

		d = length(light.pos - light_ray.ori);
		shade_obj = curr_obj;
		//this basically means that each transparent object between me and my light will affect
		//the amount and color of the light that's transmitted
		while ((shade_obj = get_shadow_intersect(scene, &light_ray, &d)) != 0 && shade_obj != curr_obj)
		{
			light_ray.ori = light_ray.ori + d * light_ray.dir + 0.01f;
			k *= shade_obj->refr;
			light.col *= ((shade_obj->perlin.type) ? perlin_gen_texture(shade_obj, scene, light_ray.ori) : shade_obj->col);
			light.col *= (shade_obj->checkw || shade_obj->checkh) ? get_checkerboard_color(shade_obj, &light_ray) : 1.f;
			light.col *= (shade_obj->refr > 0.5f ? shade_obj->refr : 1.f - shade_obj->refr);
			// light.col += (shade_obj->refr <= 0.5f ? shade_obj->refr : 1.f - shade_obj->refr) * ((shade_obj->perlin.type) ? perlin_gen_texture(shade_obj, scene, light_ray.ori) : shade_obj->col);
			curr_obj = shade_obj;
		}
		curr_obj = tmp;
		k *= dot(n_hit.dir, light_ray.dir); //this will be place to add different light properties
		col += mat * normalize_col(light.col * (k < 0.f ? 0.f : k));
		if (k > 0.f)
		{
			k = (curr_obj->shine != 0.f ? shine(&light, n_hit, ray, curr_obj->shine) : 0.f);
			col += k * light.col;
		}
		++i;
		if (scene->effect == 4)
			col += curr_obj->col * light.col * cel_shading(scene->ambient, light_ray.dir, n_hit.dir);
	}
	col = (col < scene->ambient * mat) ? scene->ambient * mat : col;
	return (normalize_col(col));
}


float3		lights(__global t_scene *scene, float3 mat, t_ray n_hit, t_ray *ray, __global t_obj *curr_obj)
{
	int		i;
	float	k;
	float	d = 0.f;
	float3	col = (float3)(0.f);
	t_ray				light_ray;
	t_light				light;
	__global t_obj		*shade_obj;
	__global t_obj		*tmp;

	tmp = curr_obj;
	i = 0;
	while (i < scene->num_light)
	{
		light = scene->lights[i];
		light_ray.ori = n_hit.ori + 0.02f * n_hit.dir;
		light_ray.dir = normalize(light.pos - light_ray.ori);
		k = 1.f;

		d = length(light.pos - light_ray.ori);
		shade_obj = curr_obj;
		//this basically means that each transparent object between me and my light will affect
		//the amount and color of the light that's transmitted
		while ((shade_obj = get_shadow_intersect(scene, &light_ray, &d)) != 0 && shade_obj != curr_obj)
		{
			light_ray.ori = light_ray.ori + d * light_ray.dir + 0.01f;
			k *= shade_obj->refr;
			light.col *= ((shade_obj->perlin.type) ? perlin_gen_texture(shade_obj, scene, light_ray.ori) : shade_obj->col);
			light.col *= (shade_obj->checkw || shade_obj->checkh) ? get_checkerboard_color(shade_obj, &light_ray) : 1.f;
			light.col *= (shade_obj->refr > 0.5f ? shade_obj->refr : 1.f - shade_obj->refr);
			// light.col += (shade_obj->refr <= 0.5f ? shade_obj->refr : 1.f - shade_obj->refr) * ((shade_obj->perlin.type) ? perlin_gen_texture(shade_obj, scene, light_ray.ori) : shade_obj->col);
			curr_obj = shade_obj;
		}
		curr_obj = tmp;
		k *= dot(n_hit.dir, light_ray.dir); //this will be place to add different light properties
		col += mat * normalize_col(light.col * (k < 0.f ? 0.f : k));
		if (k > 0.f)
		{
			k = (curr_obj->shine != 0.f ? shine(&light, n_hit, ray, curr_obj->shine) : 0.f);
			col += k * light.col;
		}
		++i;
		if (scene->effect == 4)
			col += curr_obj->col * light.col * cel_shading(scene->ambient, light_ray.dir, n_hit.dir);
	}
	col = (col < scene->ambient * mat) ? scene->ambient * mat : col;
	return (normalize_col(col));
}

float3		cast_ray(__global t_scene *scene, t_ray *ray, int depth)
{
	__global t_obj	*curr_obj;
	t_ray			n_hit;
	float3			col = (float3)(0.f);
	float			strength = 1.f;
	float 			diff_coef, refr_coef, refl_coef, t;
	float3 			mat;
	int				outside;

	while (strength > 0.0f && depth <= scene->bouncenb)
	{
		//get ray-object intersection and corresponding norml vector
		t = FLT_MAX;
		if ((curr_obj = get_obj_intersect(scene, ray, &t)) == 0)
			return (col += scene->bg * strength);
		n_hit.ori = ray->ori + t * ray->dir;
		n_hit.dir = get_phit_normal(ray, n_hit.ori, curr_obj, t);

		outside = (dot(ray->dir, n_hit.dir) < 0) ? 1 : 0;
		//calculate coefficients of material properties (with fresnel or not)
		if (curr_obj->ior && !curr_obj->refr)
			refl_coef = fresnel(ray->dir, n_hit.dir, curr_obj->ior) * strength;
		else
		{
			refl_coef = curr_obj->refl * strength;
			refr_coef = curr_obj->refr * (1.f - refl_coef) * strength;
		}
		diff_coef = strength * (1.f - refr_coef - refl_coef);

		//add current object diffuse to final pixel color
		if (diff_coef > 0.f)
		{
			//calculate diffuse color with color effects (perlin/water/ texture later)
			mat = (curr_obj->perlin.type != 0) ? perlin_gen_texture(curr_obj, scene, n_hit.ori) : curr_obj->col;
			mat = (curr_obj->checkw || curr_obj->checkh) ? get_checkerboard_color(curr_obj, &n_hit) : mat;
			//add texture calculations here later

			//get add diff color after lights act on mat
			col += diff_coef * lights(scene, mat, n_hit, ray, curr_obj);
			strength -= diff_coef;
		}

		if (curr_obj->ior && !curr_obj->refr)
		{
			if (refl_coef < 1.f)
			{
				ray->ori = (outside) ? n_hit.ori - 0.2f * n_hit.dir : n_hit.ori + 0.2f * n_hit.dir;
				ray->dir = normalize(refract(ray->dir, n_hit.dir, curr_obj->ior));
				if ((curr_obj = get_obj_intersect(scene, ray, &t)))
					col += refl_coef * lights2(scene, mat, n_hit, ray, curr_obj);
			}
			ray->ori = n_hit.ori + 0.02f * n_hit.dir;
			ray->dir = normalize(reflect(ray->dir, n_hit.dir));
			strength *= refl_coef;
		}
		else
		{
			if (refl_coef > refr_coef)
			{
				ray->ori = n_hit.ori + 0.02f * n_hit.dir;
				ray->dir = normalize(reflect(ray->dir, n_hit.dir));
				strength *= refl_coef;
			}

			else if (refr_coef >= refl_coef)
			{
				ray->ori = (outside) ? n_hit.ori - 0.02f * n_hit.dir : n_hit.ori + 0.02f * n_hit.dir;
				ray->dir = normalize(refract(ray->dir, n_hit.dir, curr_obj->ior));
				strength *= refr_coef;
			}
		}
		++depth;
	}
	float fogAmount = exp(-t * scene->fogdist / 100000);
	col = mix(scene->fogcol, col, fogAmount);
	return (normalize_col(col));
}

__kernel void render_scene(
	__global t_scene	*scene,
	__global int		*img)
{
	int		x, y;
	float	xx, yy;
	float	angle = tan(radians(scene->cam.fov * 0.5f));
	t_ray	ray;

	x = get_global_id(0);
	y = get_global_id(1);
	xx = (2 * ((x + 0.5) / (float)scene->win_x) - 1);
	xx *= angle * scene->win_x / (float)scene->win_y;
	yy = (1 - 2 * ((y + 0.5) / (float)scene->win_y)) * angle;

	ray.ori = scene->cam.pos;
	ray.dir = normalize((float3)(xx, yy, -1));
	ray.dir = rotate_full(ray.dir, scene->cam.rot);
	img[x + y * scene->win_x] = float3_to_int(check_effect(scene, cast_ray(scene, &ray, 0)));
}
