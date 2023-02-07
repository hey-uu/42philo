/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:06:13 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/07 15:45:05 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

void	print_philo_state(t_philo *philo, int state)
{
	struct timeval	now;
	size_t			time;
	static char		*msg[] = {
	[NOW_READY] = MSG_NOW_READY,
	[PICK_UP_LEFT_FORK] = MSG_GETTING_FORK,
	[PICK_UP_RIGHT_FORK] = MSG_GETTING_FORK,
	[EAT] = MSG_EATING,
	[SLEEP] = MSG_SLEEPING,
	[THINK] = MSG_THINKING,
	};

	pthread_mutex_lock(&philo->shared->print_lock);
	gettimeofday(&now, NULL);
	time = get_time_interval_ms(&philo->shared->start_time, &now);
	printf("%zu %d %s\n", time, philo->id, msg[state]);
	pthread_mutex_unlock(&philo->shared->print_lock);
}

size_t	get_time_interval_us(struct timeval *start, struct timeval *now)
{
	return ((now->tv_sec - start->tv_sec) * 1000000 + \
			(now->tv_usec - start->tv_usec));
}

size_t	get_time_interval_ms(struct timeval *start, struct timeval *now)
{
	return ((now->tv_sec - start->tv_sec) * 1000 + \
			(now->tv_usec - start->tv_usec) / 1000);
}

t_bool	is_single_philo(t_philo *philo)
{
	if (philo->lfork != philo->rfork)
		return (FALSE);
	pthread_mutex_lock(philo->lfork);
	update_philo_state(philo, PICK_UP_LEFT_FORK);
	print_philo_state(philo, PICK_UP_LEFT_FORK);
	return (TRUE);
}

t_bool	is_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->monitor_lock);
	if (philo->shared->is_done == TRUE)
	{
		pthread_mutex_unlock(&philo->shared->monitor_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->shared->monitor_lock);
	return (FALSE);
}

void	philo_unlock_mutexes(t_philo *philo)
{
	pthread_mutex_lock(philo->state_lock);
	if (philo->state == PICK_UP_LEFT_FORK
		|| philo->state == PICK_UP_RIGHT_FORK)
		pthread_mutex_unlock(philo->lfork);
	if (philo->state == PICK_UP_RIGHT_FORK)
		pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->state_lock);
}
