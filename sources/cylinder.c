/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:14:09 by nbethany          #+#    #+#             */
/*   Updated: 2019/11/18 19:14:12 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			intersect_cylinder(t_cylinder cylinder, t_ray *ray, double *hit)
{
	t_vector3	distance;
	t_vector3	dir;
	double		a;
	double		b;
	double		c;

	dir = cylinder.dir;
	distance = sub_vector3(ray->origin, cylinder.center);
	a = dot_vector3(ray->dir, ray->dir) - (dot_vector3(ray->dir, dir)
			* dot_vector3(ray->dir, dir));
	b = 2 * (dot_vector3(ray->dir, distance) - (dot_vector3(ray->dir, dir)
			* dot_vector3(distance, dir)));
	c = dot_vector3(distance, distance) - (dot_vector3(distance, dir)
			* dot_vector3(distance, dir)) - cylinder.radius * cylinder.radius;
	if (b * b - 4.0f * a * c < T_RAY_MIN)
		return (0);
	else
		return (calc_intersect(a, b, c, hit));
}

int			find_closest_cylinder(t_ray ray, t_rtv *rtv, double *t)
{
	int	i;
	int	current;

	i = 0;
	current = -1;
	while (i < rtv->nbr[CYLINDER])
	{
		if (intersect_cylinder(rtv->cylinder[i], &ray, t))
			current = i;
		i++;
	}
	return (current);
}

t_vector3	find_norm_cylinder(t_vector3 hit_point,
		t_vector3 center, t_vector3 dir)
{
	t_vector3	norm;
	t_vector3	x;
	double		d;

	norm = sub_vector3(hit_point, center);
	d = dot_vector3(norm, dir) / dot_vector3(dir, dir);
	x = scale_vector3(dir, d);
	norm = normalize(sub_vector3(norm, x));
	return (norm);
}
