int		float3_to_int(float3 col)
{
	t_col res;

	res.i = 0;
	res.c[2] = fmin(col.s0 * 255, 255);
	res.c[1] = fmin(col.s1 * 255, 255);
	res.c[0] = fmin(col.s2 * 255, 255);
	res.c[3] = 255;
	return (res.i);
}

float   ft_clamp(float x, float min, float max)
{
	if (x < min)
		x = min;
	else if (x > max)
		x = max;
	return (x);
}

float3		normalize_col(float3 col)
{
	float max;

	max = fmax(col.s0, col.s1);
	max = fmax(max, col.s2);
	max = fmax(max, 1.f);
	return (col /= max);
}
