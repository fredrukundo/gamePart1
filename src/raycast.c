/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frukundo <frukundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 03:32:15 by frukundo          #+#    #+#             */
/*   Updated: 2024/04/20 03:32:16 by frukundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
	@desc:
	- g->ray.angle: Sets the initial angle for raycasting based on the player's
		direction (S, W, N).The angles are set to 90, 180, or 270 degrees, respectively.
	- g->ray.hfov: Sets the half field of view (FOV) to 30 degrees.
	- g->ray.incre_angle: Angle difference between one ray and the next one
		(2 * HFOV / window_width)
	- g->ray.precision: Sets the Size of 'steps' taken every iteration.
	- g->ray.lim: Sets a Limit of the distance the player can view.
*/
void	init_ray(t_game *g)
{
	g->ray.angle = 0;
	if (g->pl.dir == 'S')
		g->ray.angle = 90;
	else if (g->pl.dir == 'W')
		g->ray.angle = 180;
	else if (g->pl.dir == 'N')
		g->ray.angle = 270;
	g->ray.hfov = 30;
	g->ray.incre_angle = 2 * g->ray.hfov / WIN_W;
	g->ray.precision = 50;
	g->ray.lim = 11;
}

/*
	@desc:
	- From the the player's position, we move the ray forward incrementing the x's and y's coordinates of the ray.
		(ray.x += ray_cos; ray.y += ray_sin;) where :ray_cos = cos(degree_to_radians(ray_angle)) / g->ray.precision;
		ray_sin = sin(degree_to_radians(ray_angle)) / g->ray.precision;
	- Repeat this step until we reach the limit or we hit a wall.
	- Calculate the distance between the player's and the ray's position using the euclidean distance
		( distance = sqrt(powf(x - pl.x - 0.5, 2.) + powf(y - pl.y - 0.5, 2.)); )
	- Fix fisheye(distance = distance * cos(degree_to_radians(ray_angle - g->ray.angle)))
	- distance is really helpful to calculate the height of the wall height:
		( wall_height = (window_height / (1.5 * distance)); )
	NB:
	Depending on what the ray hits:
	- If it hits a wall ('1' or 'c' in the map), a red pixel is drawn on the minimap.
	- If it's close to the player's viewing direction, a green pixel is drawn.
	- Otherwise, a light blue pixel is drawn.
	- Finally, a yellow square is drawn on the minimap to represent the player's position.
*/
float	distance_to_wall(t_game *g, float ray_angle)
{
	float	d;

	g->ray.cos = cos(degree_to_radians(ray_angle)) / g->ray.precision;
	g->ray.sin = sin(degree_to_radians(ray_angle)) / g->ray.precision;
	g->x = g->pl.x + 0.5;
	g->y = g->pl.y + 0.5;
	while (!ft_strchr("1c", g->map[(int)g->y][(int)g->x]) && \
		sqrt(powf(g->x - g->pl.x - 0.5, 2.) + \
		powf(g->y - g->pl.y - 0.5, 2.)) < g->ray.lim)
	{
		g->x += g->ray.cos;
		g->y += g->ray.sin;
		if (ft_strchr("1c", g->map[(int)g->y][(int)g->x]))
			my_mlx_pixel_put(&g->minimap, g->x * SIZE, g->y * SIZE, 0x00FF0000);
		else if (ray_angle - 1 < g->ray.angle && ray_angle + 1 > g->ray.angle)
			my_mlx_pixel_put(&g->minimap, g->x * SIZE, g->y * SIZE, 0x0000FF00);
		else
			my_mlx_pixel_put(&g->minimap, g->x * SIZE, g->y * SIZE, 0x00BDC1C6);
	}
	my_mlx_area_put(&g->minimap, ft_newvector((int)(g->pl.x + 0.5) * SIZE, \
		(int)(g->pl.y + 0.5) * SIZE), ft_newvector(SIZE, SIZE), 0x00FDD663);
	d = sqrt(powf(g->x - g->pl.x - 0.5, 2.) + powf(g->y - g->pl.y - 0.5, 2.));
	return (d * cos(degree_to_radians(ray_angle - g->ray.angle)));
}

/*
	@desc:
	- ray_angle: Starts from the leftmost side of the FOV and
		iteratively increases to cover the entire horizontal FOV.
	- ray_count: Counts the number of rays processed.
	- dist: Calculates the distance to the nearest wall for each ray.
	- then cub_draw function is called to draw the rays on the screen.
*/
void	cub_raycast(t_game *g)
{
	float	ray_angle;
	int		ray_count;
	float	dist;

	ray_angle = g->ray.angle - g->ray.hfov;
	ray_count = -1;
	while (++ray_count < WIN_W)
	{
		dist = distance_to_wall(g, ray_angle);
		cub_draw(g, ray_count, dist);
		ray_angle += g->ray.incre_angle;
	}
}
