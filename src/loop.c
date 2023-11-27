/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:12:36 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/27 13:40:13 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_mlx_hook(t_display *display)
{
	free_display(display);
	exit (EXIT_SUCCESS);
	return (0);
}

int	ft_loop_hook(t_display *display)
{
	display->new_img = init_screen_image(display);
	move_player(display);
	render_image(display->new_img, display);
	mlx_clear_window(display->mlx, display->win);
	if (display->old_img)
	{
		mlx_destroy_image(display->mlx, display->old_img->mlx_img);
		display->old_img = display->new_img;
	}
	else
		display->old_img = display->new_img;
	mlx_put_image_to_window(display->mlx, display->win,
		display->old_img->mlx_img, 0, 0);
	return (0);
}
