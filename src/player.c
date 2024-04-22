/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frukundo <frukundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 03:32:05 by frukundo          #+#    #+#             */
/*   Updated: 2024/04/20 04:21:54 by frukundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
	@desc:
	- moving the player based on the key pressed (k) and
		updating the player's position in the game state
*/
void	move_pl(int k, t_game *g, float ray_cos, float ray_sin)
{
	float	angle;

	angle = g->ray.angle;
	if (k == KEY_A)
		angle = g->ray.angle - 90;
	else if (k == KEY_S)
		angle = g->ray.angle - 180;
	else if (k == KEY_D)
		angle = g->ray.angle + 90;
	ray_cos = cos(degree_to_radians(angle)) * g->pl.speed;
	ray_sin = sin(degree_to_radians(angle)) * g->pl.speed;
	if (!ft_strchr("1c", g->map[(int)(g->pl.y + 0.5 + \
			(3 * ray_sin))][(int)(g->pl.x + 0.5)]))
		g->pl.y += ray_sin;
	if (!ft_strchr("1c", \
		g->map[(int)(g->pl.y + 0.5)][(int)(g->pl.x + 0.5 + (3 * ray_cos))]))
		g->pl.x += ray_cos;
}
