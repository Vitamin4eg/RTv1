/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 21:28:51 by nbethany          #+#    #+#             */
/*   Updated: 2019/09/26 21:28:53 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vector3	new_vector3(double x, double y, double z)
{
	t_vector3	vec_new;

	vec_new.x = x;
	vec_new.y = y;
	vec_new.z = z;
	return (vec_new);
}

t_vector3	add_vector3(t_vector3 vec1, t_vector3 vec2)
{
	t_vector3	vec_add;

	vec_add.x = vec1.x + vec2.x;
	vec_add.y = vec1.y + vec2.y;
	vec_add.z = vec1.z + vec2.z;
	return (vec_add);
}

t_vector3	sub_vector3(t_vector3 vec1, t_vector3 vec2)
{
	t_vector3	vec_sub;

	vec_sub.x = vec1.x - vec2.x;
	vec_sub.y = vec1.y - vec2.y;
	vec_sub.z = vec1.z - vec2.z;
	return (vec_sub);
}

double		dot_vector3(t_vector3 vec1, t_vector3 vec2)
{
	double dot;

	dot = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (dot);
}

t_vector3	cross_vector3(t_vector3 vec1, t_vector3 vec2)
{
	t_vector3	vec_mult;

	vec_mult.x = vec1.y * vec2.z - vec1.z * vec2.y;
	vec_mult.y = vec1.z * vec2.x - vec1.x * vec2.z;
	vec_mult.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (vec_mult);
}
