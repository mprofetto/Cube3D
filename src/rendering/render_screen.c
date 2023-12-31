/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:48:37 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/04 19:06:45 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	render_background(t_img *image, t_display *display);
static void	cast_ray(t_display *display, t_ray *ray, int *side);
static void	update_walls_perp_dist(t_map *map, t_ray *ray, int *x, int *side);
static void	render_minimap(t_img *image, t_display *display);

void	render_image(t_img *image, t_display *display)
{
	t_ray	ray;
	int		x;
	int		side;

	render_background(image, display);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		side = 0;
		init_ray(&ray, display->map, &x);
		cast_ray(display, &ray, &side);
		update_walls_perp_dist(display->map, &ray, &x, &side);
		draw_column(display, &ray, &x, &side);
	}
	render_sprites(display->map, image, display->map->sprite_texture);
	render_minimap(image, display);
}

static void	render_background(t_img *image, t_display *display)
{
	int	x;
	int	y;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT)
		{
			if (y < SCREEN_HEIGHT / 2)
				put_pixel_on_img(image, x, y, display->map->celling_color);
			else
				put_pixel_on_img(image, x, y, display->map->floor_color);
		}
	}
}

static void	cast_ray(t_display *display, t_ray *ray, int *side)
{
	while (ray->hit == 0)
	{
		if (ray->side_distance.x < ray->side_distance.y)
		{
			ray->side_distance.x += ray->delta_distance.x;
			ray->origin.x += ray->step_x;
			*side = 0;
		}
		else
		{
			ray->side_distance.y += ray->delta_distance.y;
			ray->origin.y += ray->step_y;
			*side = 1;
		}
		if (display->map->tiles[ray->origin.x][ray->origin.y] == '1')
			ray->hit = 1;
		else if (display->map->tiles[ray->origin.x][ray->origin.y] == 'D'
			&& get_door_status(display->map->door_lst, ray->origin.x,
			ray->origin.y) == DOOR_IS_CLOSED)
			ray->hit = 2;
	}
}

/*
	Corrects the perspective to avoid the fish-eye effect
*/
static void	update_walls_perp_dist(t_map *map, t_ray *ray, int *x, int *side)
{
	if (*side == 0)
		map->player->walls_perp_distance[*x]
			= (ray->side_distance.x - ray->delta_distance.x);
	else
		map->player->walls_perp_distance[*x]
			= (ray->side_distance.y - ray->delta_distance.y);
}

static void	render_minimap(t_img *image, t_display *display)
{
	int		x;
	int		y;
	t_dot	pixel;

	x = MINIMAP_CENTER_X - MINIMAP_DIAMETER / 2;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < MINIMAP_DIAMETER)
		{
			if (pixel_is_in_minimap_border(x, y) == 0)
				put_pixel_on_img(image, x, y,
					display->map->minimap_border_color);
			else if (pixel_is_in_minimap(x, y) == 0)
			{
				pixel.x = x;
				pixel.y = y;
				put_pixel_on_minimap(image, display->map, &pixel);
			}
		}
	}
}
