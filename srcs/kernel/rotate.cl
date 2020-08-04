float3	rotate_x(float3 v, float theta)
{
	float3	res;
	float	cos_t;
	float	sin_t;

	cos_t = cos(theta);
	sin_t = sin(theta);
	res.x = dot(v, (float3)(1, 0, 0));
	res.y = dot(v, (float3)(0, cos_t, -sin_t));
	res.z = dot(v, (float3)(0, sin_t, cos_t));
	return (res);
}

float3	rotate_y(float3 v, float theta)
{
	float3	res;
	float	cos_t;
	float	sin_t;

	cos_t = cos(theta);
	sin_t = sin(theta);
	res.x = dot(v, (float3)(cos_t, 0, sin_t));
	res.y = dot(v, (float3)(0, 1, 0));
	res.z = dot(v, (float3)(-sin_t, 0, cos_t));
	return (res);
}

float3	rotate_z(float3 v, float theta)
{
	float3	res;
	float	cos_t;
	float	sin_t;

	cos_t = cos(theta);
	sin_t = sin(theta);
	res.x = dot(v, (float3)(cos_t, -sin_t, 0));
	res.y = dot(v, (float3)(sin_t, cos_t, 0));
	res.z = dot(v, (float3)(0, 0, 1));
	return (res);
}

float3	rotate_full(float3 ori, float3 rot)
{
	float3	res;

	res = ori;
	res = rotate_z(res, rot.z);
	res = rotate_x(res, rot.x);
	res = rotate_y(res, rot.y);
	return (res);
}
