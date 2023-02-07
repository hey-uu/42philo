/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:51:42 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/07 15:54:26 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

static void	philo_behave(\
			struct timeval *start, struct timeval *end, size_t time)
{
	usleep(time * 0.8);
	gettimeofday(end, NULL);
	while (get_time_interval_us(start, end) + 1000 < time)
	{
		usleep(100);
		gettimeofday(end, NULL);
	}
	while (get_time_interval_us(start, end) < time)
	{
		gettimeofday(end, NULL);
	}
}

static t_done	philo_pick_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	update_philo_state(philo, PICK_UP_LEFT_FORK);
	if (is_done(philo) == TRUE)
		return (DONE);
	print_philo_state(philo, PICK_UP_LEFT_FORK);
	pthread_mutex_lock(philo->rfork);
	update_philo_state(philo, PICK_UP_RIGHT_FORK);
	if (is_done(philo) == TRUE)
		return (DONE);
	print_philo_state(philo, PICK_UP_RIGHT_FORK);
	return (CONTINUE);
}

static t_done	philo_eat(t_philo *philo)
{
	print_philo_state(philo, EAT);
	update_philo_last_meal_start(philo);
	philo_behave(\
	&philo->time.now, &philo->time.last_meal_end, philo->shared->time_to_eat);
	update_philo_meal_cnt(philo);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	return (CONTINUE);
}

static t_done	philo_sleep_or_think(t_philo *philo)
{
	if (is_done(philo) == DONE)
		return (DONE);
	print_philo_state(philo, SLEEP);
	philo_behave(\
	&philo->time.last_meal_end, &philo->time.now, philo->shared->time_to_sleep);
	if (is_done(philo) == DONE)
		return (DONE);
	print_philo_state(philo, THINK);
	update_philo_state(philo, THINK);
	return (CONTINUE);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (is_single_philo(philo) == TRUE)
		return (NULL);
	if ((philo->id & 1) == 1)
		usleep(philo->shared->time_to_eat / 2);
	while (1)
	{
		if (philo_pick_forks(philo) == DONE)
			break ;
		if (philo_eat(philo) == DONE)
			break ;
		if (philo_sleep_or_think(philo) == DONE)
			break ;
	}
	philo_unlock_mutexes(philo);
	return (NULL);
}
