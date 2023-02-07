/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:04:29 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/07 15:51:10 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

static t_bool	philo_starved_to_death(t_philo *philo, t_shared_data *shared)
{
	pthread_mutex_lock(philo->time_lock);
	gettimeofday(&philo->time.death_check_time, NULL);
	if (get_time_interval_us(\
		&philo->time.last_meal_start, &philo->time.death_check_time) \
											>= shared->time_to_die)
	{
		pthread_mutex_unlock(philo->time_lock);
		pthread_mutex_lock(&shared->monitor_lock);
		shared->is_done = TRUE;
		pthread_mutex_unlock(&shared->monitor_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->time_lock);
	return (FALSE);
}

static int	get_done_count(int *done_cnt, t_philo *philo)
{
	if (philo->shared->must_eat_num == NO_OPT)
		return (0);
	pthread_mutex_lock(philo->eat_num_lock);
	if (philo->eat_cnt >= philo->shared->must_eat_num)
	{
		pthread_mutex_unlock(philo->eat_num_lock);
		(*done_cnt)++;
	}
	pthread_mutex_unlock(philo->eat_num_lock);
	return (*done_cnt);
}

t_philo	*monitor_philos(t_philo *philos, t_shared_data *shared)
{
	int	i;
	int	done_cnt;

	while (1)
	{
		i = 0;
		done_cnt = 0;
		usleep(7000);
		while (i < shared->philo_num)
		{
			if (philo_starved_to_death(&philos[i], shared) == TRUE)
				return (&philos[i]);
			if (get_done_count(&done_cnt, &philos[i]) == shared->philo_num)
			{
				pthread_mutex_lock(&shared->monitor_lock);
				shared->is_done = TRUE;
				pthread_mutex_unlock(&shared->monitor_lock);
				return (NULL);
			}
			i++;
		}
	}
}
