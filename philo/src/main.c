/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:54:13 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/05 16:52:27 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

static void	terminate_program(t_info *info)
{
	join_threads(info->philos, info->shared.philo_num);
	pthread_mutex_destroy(&info->shared.monitor_lock);
	pthread_mutex_destroy(&info->shared.print_lock);
	destroy_mutex_array(info->forks, info->shared.philo_num);
	destroy_mutex_array(info->state_locks, info->shared.philo_num);
	destroy_mutex_array(info->time_locks, info->shared.philo_num);
}

int	main(int argc, char **argv)
{
	static t_info	info;

	if (init_info(&info, argc, argv) == ERROR)
		return (1);
	if (seat_philos(&info) == ERROR)
		return (1);
	monitor_philos(info.philos, &info.shared);
	terminate_program(&info);
	return (0);
}
