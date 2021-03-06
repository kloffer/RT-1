/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_gui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 18:33:30 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/23 18:33:32 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

void	gui_interaction_event(t_rt *rt_data, SDL_Event *event)
{
	int	i;

	i = -1;
	while (++i < rt_data->cl_data.num_of_objects)
	{
		if (rt_data->objects_arr[i].is_cartoon)
			change_object(&rt_data->objects_arr[i], check_arrow_type(event));
	}
}

void	foot_panel_interaction_event(t_rt *rt_data, SDL_Event *event)
{
	int			flag;

	flag = check_foot_press_type(event);
	if (flag == FILTERS)
	{
		rt_data->gui.filter_gui = !rt_data->gui.filter_gui;
		rt_data->filter = NONE;
	}
	else if (flag == ALIASING)
		rt_data->aliasing = !rt_data->aliasing;
	else
	{
		make_screenshot(rt_data);
	}
}

void	filter_panel_interaction_event(t_rt *rt_data, SDL_Event *event)
{
	if (event->button.x >= 0 && event->button.x <= 300
		&& event->button.y > SCR_SIZE - 430
		&& event->button.y <= SCR_SIZE - 350)
		rt_data->filter = GREYSCALE;
	else if (event->button.x >= 0 && event->button.x <= 300
			&& event->button.y > SCR_SIZE - 350
			&& event->button.y <= SCR_SIZE - 280)
		rt_data->filter = PIXEL;
	else if (event->button.x >= 0 && event->button.x <= 300
			&& event->button.y > SCR_SIZE - 280
			&& event->button.y <= SCR_SIZE - 200)
		rt_data->filter = SEPIA;
	else if (event->button.x >= 0 && event->button.x <= 300
			&& event->button.y > SCR_SIZE - 200
			&& event->button.y <= SCR_SIZE - 130)
		rt_data->filter = NEGATIVE;
}

void	create_gui(t_rt *rt_data, SDL_Event *event, int flag)
{
	if (flag == FOOT_GUI)
		foot_panel_interaction_event(rt_data, event);
	else if (flag == FIGURE_GUI)
		gui_interaction_event(rt_data, event);
	else if (flag == FILTER_GUI)
		filter_panel_interaction_event(rt_data, event);
}

int		mouse_click_event(t_rt *rt_data, SDL_Event *event)
{
	t_ray		primary_ray;
	t_intersect	closest_inter;
	t_dot		pixel;
	int			i;

	pixel = (t_dot){event->button.x, event->button.y};
	primary_ray = compute_ray(rt_data->cl_data.camera, pixel);
	closest_inter = find_closest_inter(rt_data->cl_data,
									rt_data->objects_arr, primary_ray);
	i = -1;
	if (check_if_in_gui(rt_data, event) != NO_GUI)
		create_gui(rt_data, event, check_if_in_gui(rt_data, event));
	else
	{
		if (closest_inter.distance != INFINITY)
			while (++i < rt_data->cl_data.num_of_objects)
				swap_cartoon(closest_inter, rt_data, i);
	}
	draw_scene(rt_data);
	SDL_UpdateWindowSurface(rt_data->window);
	return (0);
}
