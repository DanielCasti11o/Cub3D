/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:21:57 by migugar2          #+#    #+#             */
/*   Updated: 2025/10/22 20:58:08 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	t_color	out;

	out.r = r;
	out.g = g;
	out.b = b;
	out.a = a;
	return (out);
}

static int	parse_color_component(char **str, uint8_t *component)
{
	int	value;

	value = 0;
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '+')
		(*str)++;
	if (!ft_isdigit(**str))
		return (perror_unexpectedchar(**str), 1);
	while (ft_isdigit(**str))
	{
		value = value * 10 + (**str - '0');
		if (value > 255)
			return (perror_overflow(), 1);
		(*str)++;
	}
	*component = (uint8_t)value;
	while (ft_isspace(**str))
		(*str)++;
	return (0);
}

int	parse_color(char *str, t_color *color)
{
	if (parse_color_component(&str, &color->r) == 1)
		return (1);
	if (*str != ',')
		return (perror_unexpectedchar(*str), 1);
	str++;
	if (parse_color_component(&str, &color->g) == 1)
		return (1);
	if (*str != ',')
		return (perror_unexpectedchar(*str), 1);
	str++;
	if (parse_color_component(&str, &color->b) == 1)
		return (1);
	if (*str != '\n' && *str != '\0')
		return (perror_unexpectedchar(*str), 1);
	color->a = 255;
	return (0);
}

/*
uint32_t	pack_color(int endian, t_color color)
{
	uint32_t	packed;

	if (endian == 0)
		packed = (((uint32_t)color.a << 24)
				| (color.r << 16) | (color.g << 8) | color.b);
	else
		packed = ((color.a) | (color.r << 8) | (color.g << 16)
				| ((uint32_t)color.b << 24));
	return (packed);
}

t_color	unpack_color(int endian, uint32_t packed)
{
	t_color	color;

	if (endian == 0)
	{
		color.a = (packed >> 24) & 0xFF;
		color.r = (packed >> 16) & 0xFF;
		color.g = (packed >> 8) & 0xFF;
		color.b = packed & 0xFF;
	}
	else
	{
		color.a = packed & 0xFF;
		color.r = (packed >> 8) & 0xFF;
		color.g = (packed >> 16) & 0xFF;
		color.b = (packed >> 24) & 0xFF;
	}
	return (color);
}
*/
