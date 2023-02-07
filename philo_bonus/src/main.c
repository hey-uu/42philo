/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:54:13 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/07 15:45:18 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static void	terminate_program(t_info *info, t_philo *philo)
{
	size_t	death_time;

	join_threads(info->philos, info->shared.philo_num);
	if (philo)
	{
		death_time = get_time_interval_ms(\
		&philo->shared->start_time, &philo->time.death_check_time);
		printf("%zu %d %s\n", death_time, philo->id, MSG_DEAD);
	}
	pthread_mutex_destroy(&info->shared.monitor_lock);
	pthread_mutex_destroy(&info->shared.print_lock);
	destroy_mutex_array(info->forks, info->shared.philo_num);
	destroy_mutex_array(info->state_locks, info->shared.philo_num);
	destroy_mutex_array(info->time_locks, info->shared.philo_num);
}

int	main(int argc, char **argv)
{
	static t_info	info;
	t_philo			*philo;

	if (init_info(&info, argc, argv) == ERROR)
		return (1);
	if (seat_philos(&info) == ERROR)
		return (1);
	philo = monitor_philos(info.philos, &info.shared);
	terminate_program(&info, philo);
	return (0);
}
