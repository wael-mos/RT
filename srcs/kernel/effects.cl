float3	check_effect(__global t_scene *scene, float3 col)
{
	if (scene->effect == 1)
		col = sepiarize(col);
	else if (scene->effect == 3)
		col = invert(col);
	col = desaturate(col, 1 - scene->saturation);
	col = gamma_correction(col, scene->gamma);
	if (scene->effect == 2)
	{
		col = desaturate(col, 1);
		col = blackwhite(col);
	}
	return (col);
}

float	cel_shading(float ambient, float3 dir, float3 ndir)
{
	float intensity;
	intensity = dot(ndir, normalize(dir));
	intensity = ceil(intensity * 4) / 4;
	intensity = max(intensity, ambient);
	return (intensity);
}

float3 blackwhite(float3 col)
{
	float grayscale;
	float3 ret;

	grayscale = (col.s0 + col.s1 + col.s2) / 3;
	ret = (float3)(grayscale);
	return (ret);
}

float3 sepiarize(float3 col)
{
	float3 ret;
	ret.s2 = (col.s0 * 0.393f) + (col.s1 * 0.769f) + (col.s2 * 0.189f);
	ret.s1 = (col.s0 * 0.349f) + (col.s1 * 0.686f) + (col.s2 * 0.168f);
	ret.s0 = (col.s0 * 0.272f) + (col.s1 * 0.534f) + (col.s2 * 0.131f);
	return (ret);
}

float3 invert(float3 col)
{
	float3 ret;

	ret.s0 = fabs(1 - col.s0);
	ret.s1 = fabs(1 - col.s1);
	ret.s2 = fabs(1 - col.s2);
	return (ret);
}

float3 desaturate(float3 col, float amount)
{
	float3 ret;
	float f;
	float l;

	f = amount;
	l = 0.3 * col.s0 + 0.6 * col.s1 + 0.1 * col.s2;
	ret = col + f * (l - col);
	return (ret);
}

float3 gamma_correction(float3 col, float gamma)
{
	float3 ret;

	ret.s0 = pow(col.s0, (1.0f/gamma));
	ret.s1 = pow(col.s1, (1.0f/gamma));
	ret.s2 = pow(col.s2, (1.0f/gamma));
	return (ret);
}
