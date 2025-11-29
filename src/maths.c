/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:15:37 by migugar2          #+#    #+#             */
/*   Updated: 2025/11/29 17:23:46 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	degrees(double grad)
{
	double	rad;

	rad = grad * (PI / 180);
	return (rad);
}

double	get_delta_dist(float rdir)
{
	if (fabsf(rdir) < 1e-6)
		return (1e30);
	return (1.0 / fabsf(rdir));
}
