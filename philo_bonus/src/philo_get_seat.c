/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_get_seat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:19:57 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/05 18:14:00 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_initial_last_meal_start_time(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->shared.philo_num)
	{
		info->philos[i].time.last_meal_start.tv_sec = \
			info->shared.start_time.tv_sec;
		info->philos[i].time.last_meal_start.tv_usec = \
			info->shared.start_time.tv_usec;
		i++;
	}
}

t_error	seat_philos(t_info *info)
{
	int	i;

	i = 0;
	gettimeofday(&(info->shared.start_time), NULL);
	set_initial_last_meal_start_time(info);
	while (i < info->shared.philo_num)
	{
		if (pthread_create(&(info->philos[i].tid), NULL, \
							philo_routine, &(info->philos[i])))
		{
			handle_thread_create_error(info, i);
			return (ERROR);
		}
		i++;
	}
	return (ERROR_NONE);
}
