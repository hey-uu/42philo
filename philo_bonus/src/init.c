/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:54:55 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/05 18:16:36 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

static t_error	init_shared_locks(t_shared_data *shared)
{
	if (pthread_mutex_init(&shared->print_lock, NULL) > 0)
	{
		print_err_msg(ERRCODE_FAILED_MUTEX_INIT);
		return (ERROR);
	}
	if (pthread_mutex_init(&shared->monitor_lock, NULL) > 0)
	{
		pthread_mutex_destroy(&shared->print_lock);
		print_err_msg(ERRCODE_FAILED_MUTEX_INIT);
		return (ERROR);
	}
	if (shared->must_eat_num == 0)
		shared->is_done = TRUE;
	else
		shared->is_done = FALSE;
	shared->done_philos = 0;
	return (ERROR_NONE);
}

static t_error	new_locks(pthread_mutex_t **locks, int number)
{
	pthread_mutex_t	*new;
	int				i;

	new = malloc(sizeof(pthread_mutex_t) * number);
	if (!new)
	{
		print_err_msg(ERRCODE_FAILED_MALLOC);
		return (ERROR);
	}
	i = 0;
	while (i < number)
	{
		if (pthread_mutex_init(&new[i], NULL) > 0)
		{
			destroy_mutex_array(new, i);
			free(new);
			print_err_msg(ERRCODE_FAILED_MUTEX_INIT);
			return (ERROR);
		}
		i++;
	}
	*locks = new;
	return (ERROR_NONE);
}

static void	init_philo(t_info *info, t_philo *philo, int id)
{
	philo->id = id;
	philo->eat_cnt = 0;
	philo->state = THINK;
	philo->time_lock = &info->time_locks[id - 1];
	philo->state_lock = &info->state_locks[id - 1];
	philo->eat_num_lock = &info->eat_num_locks[id - 1];
	philo->lfork = &info->forks[id - 1];
	philo->rfork = &info->forks[id % info->shared.philo_num];
	philo->shared = &info->shared;
}

static t_error	new_philos(t_philo **philos, t_info *info)
{
	t_philo	*new;
	int		i;

	if (info->shared.philo_num == 0)
	{
		print_err_msg(ERRCODE_NO_PHILO);
		return (ERROR);
	}
	new = malloc(sizeof(t_philo) * info->shared.philo_num);
	if (!new)
	{
		print_err_msg(ERRCODE_FAILED_MALLOC);
		return (ERROR);
	}
	i = 0;
	while (i < info->shared.philo_num)
	{
		init_philo(info, &new[i], i + 1);
		i++;
	}
	*philos = new;
	return (ERROR_NONE);
}

t_error	init_info(t_info *info, int argc, char **argv)
{
	if (parse_argv(info, argc, argv) == ERROR)
		return (ERROR);
	if (init_shared_locks(&info->shared) == ERROR)
		return (ERROR);
	if (new_locks(&info->forks, info->shared.philo_num) == ERROR)
	{
		return (handle_init_error(info, ERRLEV_NEW_FORKS));
	}
	if (new_locks(&info->state_locks, info->shared.philo_num) == ERROR)
	{
		return (handle_init_error(info, ERRLEV_NEW_STATE_LOCKS));
	}
	if (new_locks(&info->time_locks, info->shared.philo_num) == ERROR)
	{
		return (handle_init_error(info, ERRLEV_NEW_TIME_LOCKS));
	}
	if (new_locks(&info->eat_num_locks, info->shared.philo_num) == ERROR)
	{
		return (handle_init_error(info, ERRLEV_NEW_EAT_NUM_LOCKS));
	}
	if (new_philos(&info->philos, info) == ERROR)
	{
		return (handle_init_error(info, ERRLEV_NEW_PHILOS));
	}
	return (ERROR_NONE);
}
