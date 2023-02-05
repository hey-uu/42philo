/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 05:56:58 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/05 21:14:57 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

void	update_philo_state(t_philo *philo, int state)
{
	pthread_mutex_lock(philo->state_lock);
	philo->state = state;
	pthread_mutex_unlock(philo->state_lock);
}

void	update_philo_last_meal_start(t_philo *philo)
{
	pthread_mutex_lock(philo->time_lock);
	gettimeofday(&philo->time.last_meal_start, NULL);
	philo->time.now.tv_sec = philo->time.last_meal_start.tv_sec;
	philo->time.now.tv_usec = philo->time.last_meal_start.tv_usec;
	pthread_mutex_unlock(philo->time_lock);
}

void	update_philo_meal_cnt(t_philo *philo)
{
	pthread_mutex_lock(philo->eat_num_lock);
	philo->eat_cnt++;
	pthread_mutex_unlock(philo->eat_num_lock);
}
