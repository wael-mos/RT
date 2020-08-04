float3   		floor_vec(float3 a)
{
        int     x;
        int     y;
        int     z;

        x = a.x;
        y = a.y;
        z = a.z;
        return ((float3)(x, y, z));
}

float3   		fract_vec(float3 a)
{
        return (a - floor_vec(a));
}


float   		fractf(float a)
{
        return (a - floor(a));
}

float   		hash(float p)
{
        p = fractf(p * 0.011f);
        p *= p + 7.5f;
        p *= p + p;
        return (fractf(p));
}

float			noise(float3 x)
{
	// https://www.shadertoy.com/view/4dS3Wd
    float3	step;
    float3	i;
    float3	f;
    float	n;
    float3	u;
	
    step = (float3)(110.f, 241.f, 171.f);
    i = floor_vec(x);
    f = fract_vec(x);
    n = dot(i, step);
	u = f * (f * (1.f * f));
    return mix(mix(mix( hash(n + dot(step, (float3)(0.f))), hash(n + dot(step, (float3)(1.f, 0.f, 0.f))), u.x),
                   mix( hash(n + dot(step, (float3)(0.f, 1.f, 0.f))), hash(n + dot(step, (float3)(1.f, 1.f, 0.f))), u.x), u.y),
               mix(mix( hash(n + dot(step, (float3)(0.f, 0.f, 1.f))), hash(n + dot(step, (float3)(1.f, 0.f, 1.f))), u.x),
                   mix( hash(n + dot(step, (float3)(0.f, 1.f, 1.f))), hash(n + dot(step, (float3)(1.f))), u.x), u.y), u.z);
}

float			fbm(float3 pos, int octav)
{
	float   res;
	float   amp;
	float   frequency;
	float3	shift;
	
	res = 0.0f;
	amp = 0.5f;
	frequency = 2.f;
	shift = (float3)(100.f);
	while (octav--)
	{
                res += amp * noise(pos);
                pos = (frequency * pos) + shift;
                amp *= 0.50f;
	}
	return (res);
}

float3			cloud_perlin(__global t_obj *obj, float3 p_hit)
{
	float	res;
	float3	e;
	float3	col;
	
	e = (float3)(5.f);
	res = smoothstep(.1f, .2f , fabs(fbm((e + (obj->perlin.scaler * p_hit)), obj->perlin.octav)));
	res -= smoothstep(.4f, .5f, fabs(fbm((e + (obj->perlin.scaler * p_hit)), obj->perlin.octav)));
	col = (float3)(res) * obj->perlin.opacity;
	return (col);
}

float3			marble_perlin(__global t_obj *obj, __global t_scene *env, float3 p_hit)
{
	float3	col;
	float	res;
	float xyValue = ((p_hit.x * obj->perlin.linex) / env->win_x) + \
		((p_hit.y * obj->perlin.liney) / env->win_y) + obj->perlin.turbpow *\
			fbm((obj->perlin.scaler * p_hit), obj->perlin.octav);
	res = fabs(sin(xyValue * M_PI));
	col = (float3)(res) * obj->perlin.opacity;
	return (col);
}

float3			wood_perlin(__global t_obj *obj, __global t_scene *env, float3 p_hit)
{
	float3	col;
	float	res;
	float xValue = (p_hit.x - env->win_x / 2.f) / (float)env->win_x;
	float yValue = (p_hit.y - env->win_y / 2.f) / (float)env->win_y;
	float square = sqrt((xValue * xValue) + (yValue * yValue));
	
	float distValue = square + obj->perlin.turbpow * fbm((obj->perlin.scaler * p_hit), obj->perlin.octav);
	res = fabs(sin(2.f * obj->perlin.ringnb * distValue * M_PI));
	col = (float3)(res) * obj->perlin.opacity;
	return (col);
}

float3			perlin_gen_texture(__global t_obj *obj, __global t_scene *env, float3 p_hit)
{
	float3	col;

	col = obj->col;
	if (obj->perlin.type == 3)
		col += cloud_perlin(obj, p_hit);
	if (obj->perlin.type == 2)
		col += marble_perlin(obj, env, p_hit);
	if (obj->perlin.type == 1)
		col += wood_perlin(obj, env, p_hit);
	return (col);
}
