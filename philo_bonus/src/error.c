/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:59:35 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/05 18:07:46 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "struct_philo.h"
#include "philo_error.h"

void	print_err_msg(t_errcode errcode)
{
	const char	*msg[] = {
	[ERRCODE_FEW_ARGS] = ERRMSG_FEW_ARGS,
	[ERRCODE_TOO_MANY_ARGS] = ERRMSG_TOO_MANY_ARGS,
	[ERRCODE_NOT_POSITIVE] = ERRMSG_NOT_POSITIVE,
	[ERRCODE_NUMERIC_REQUIRED] = ERRMSG_NUMERIC_REQUIRED,
	[ERRCODE_OVER_INTMAX] = ERRMSG_OVER_INTMAX,
	[ERRCODE_FAILED_MUTEX_INIT] = ERRMSG_FAILED_MUTEX_INIT,
	[ERRCODE_FAILED_MALLOC] = ERRMSG_FAILED_MALLOC,
	[ERRCODE_NO_PHILO] = ERRMSG_NO_PHILO,
	[ERRCODE_THREAD_CREATE_FAILED] = ERRMSG_THREAD_CREATE_FAILED,
	[ERRCODE_THREAD_JOIN_FAILED] = ERRMSG_THREAD_JOIN_FAILED
	};

	printf("%s\n", msg[errcode]);
}

void	join_threads(t_philo *philos, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_join(philos[i].tid, NULL) > 0)
		{
			print_err_msg(ERRCODE_THREAD_JOIN_FAILED);
		}
		i++;
	}
}

void	destroy_mutex_array(pthread_mutex_t *mutex_arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&mutex_arr[i]);
		i++;
	}
	free(mutex_arr);
}

t_error	handle_init_error(t_info *info, t_errlev errlev)
{
	if (errlev >= ERRLEV_NEW_FORKS)
	{
		pthread_mutex_destroy(&info->shared.print_lock);
		pthread_mutex_destroy(&info->shared.monitor_lock);
	}
	if (errlev >= ERRLEV_NEW_STATE_LOCKS)
	{
		destroy_mutex_array(info->forks, info->shared.philo_num);
	}
	if (errlev >= ERRLEV_NEW_TIME_LOCKS)
	{
		destroy_mutex_array(info->state_locks, info->shared.philo_num);
	}
	if (errlev >= ERRLEV_NEW_EAT_NUM_LOCKS)
	{
		destroy_mutex_array(info->time_locks, info->shared.philo_num);
	}
	if (errlev >= ERRLEV_NEW_PHILOS)
	{
		destroy_mutex_array(info->eat_num_locks, info->shared.philo_num);
	}
	return (ERROR);
}

void	handle_thread_create_error(t_info *info, int created_num)
{
	print_err_msg(ERRCODE_THREAD_CREATE_FAILED);
	info->shared.is_done = TRUE;
	pthread_mutex_unlock(&(info->shared.monitor_lock));
	join_threads(info->philos, created_num);
	pthread_mutex_destroy(&info->shared.monitor_lock);
	pthread_mutex_destroy(&info->shared.print_lock);
	destroy_mutex_array(info->forks, info->shared.philo_num);
	destroy_mutex_array(info->state_locks, info->shared.philo_num);
	destroy_mutex_array(info->time_locks, info->shared.philo_num);
	destroy_mutex_array(info->eat_num_locks, info->shared.philo_num);
}
