static float	waves(float3 pos, int iterations, float frequency, float ampli, float lake)
{
	float iter = 0.0f;
    float w = 0.0f;
    float ws = 0.0f;
    while (iterations--)
	{
        float3 p = (float3)(sin(iter), 0.f, cos(iter));
		float x = dot(p, pos) * frequency;
    	float wave = exp(sin(x) - 1.f);
    	float dx = wave * cos(x);
        pos = pos + ((-dx * ampli * 0.048f) * normalize(p));
        w += wave * ampli;
        iter += 12.0f;
        frequency *= 1.18f;
		ws += (lake == 2) ? 1.f : ampli;
        ampli = mix(ampli, 0.f, (lake == 2) ? .2f : .1f);
    }
	return (w/ws);
}

float3			normal_perturb_water(float3 pos, float frequency, float ampli, float lake)
{
	float3	res;
	float3	ex;
	float3	ez;

	ex = (float3)(1.f, 0.0f, 0.0f);
	ez = (float3)(0.f, 0.0f, 1.0f);
	res.x = waves((0.002f * pos) - ex, 30, frequency, ampli, lake) - waves((0.002f * pos) + ex, 30, frequency, ampli, lake);
	res.y = 1.f;
	res.z = waves((0.002f * pos) - ez, 30, frequency, ampli, lake) - waves((0.002f * pos) + ez, 30, frequency, ampli, lake);
	res = normalize(res);
	return (res);
}
