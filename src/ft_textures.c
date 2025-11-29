/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 11:36:59 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/29 17:37:19 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_color_from_texture(t_buf *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= tex->width || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->size_line + x * (tex->bpp / 8));
	return (*(uint32_t *)dst);
}
