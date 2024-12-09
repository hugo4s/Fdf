/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: husamuel <husamuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:23:38 by husamuel          #+#    #+#             */
/*   Updated: 2024/12/05 11:24:45 by husamuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	info_to_list(t_date *info, t_point **head)
{
	t_point	*tmp;

	tmp = *head;
	while (tmp)
	{
		tmp->infra = info;
		tmp = tmp->next;
	}
}

static int	calculate_step(int start, int end)
{
	if (start < end)
		return (1);
	else
		return (-1);
}

static void	slope(int delta_x, int delta_y, t_point *start, t_point *end)
{
	int	step_x;
	int	step_y;
	int	x;
	int	y;
	int	p;

	x = start->x_pixel;
	y = start->y_pixel;
	p = 2 * delta_y - delta_x;
	step_x = calculate_step(start->x_pixel, end->x_pixel);
	step_y = calculate_step(start->y_pixel, end->y_pixel);
	while (x != end->x_pixel)
	{
		draw_point(start->infra, x, y, start);
		x += step_x;
		if (p >= 0)
		{
			y += step_y;
			p -= 2 * delta_x;
		}
		p += 2 * delta_y;
	}
}

static void	slap(int delta_x, int delta_y, t_point *start, t_point *end)
{
	int	step_x;
	int	step_y;
	int	x;
	int	y;
	int	p;

	x = start->x_pixel;
	y = start->y_pixel;
	p = 2 * delta_x - delta_y;
	step_x = calculate_step(start->x_pixel, end->x_pixel);
	step_y = calculate_step(start->y_pixel, end->y_pixel);
	while (y != end->y_pixel)
	{
		draw_point(start->infra, x, y, start);
		y += step_y;
		if (p >= 0)
		{
			x += step_x;
			p -= 2 * delta_y;
		}
		p += 2 * delta_x;
	}
}

void	bresenham(t_date *info, t_point *start, t_point *end)
{
	int	delta_x;
	int	delta_y;

	delta_x = abs(end->x_pixel - start->x_pixel);
	delta_y = abs(end->y_pixel - start->y_pixel);
	if (delta_x >= delta_y)
	{
		slope(delta_x, delta_y, start, end);
	}
	else
	{
		slap(delta_x, delta_y, start, end);
	}
	draw_point(info, end->x_pixel, end->y_pixel, end);
}