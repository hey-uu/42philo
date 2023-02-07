/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:54:59 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/07 15:39:44 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*----------------------------- STANDARD HEADERS -----------------------------*/

# include <sys/types.h>
# include <unistd.h>

/*--------------------------- USER DEFINED HEADERS ---------------------------*/

# include "philo_error.h"
# include "struct_philo.h"

/*--------------------------- FUNCTION PROTOTYPES ----------------------------*/

// error
void		print_err_msg(t_errcode errcode);
void		join_threads(t_philo *philos, int philo_num);
void		destroy_mutex_array(pthread_mutex_t *mutex_arr, int size);
t_error		handle_init_error(t_info *info, t_errlev errlev);
void		handle_thread_create_error(t_info *info, int created_num);

// init
t_error		init_info(t_info *info, int argc, char **argv);
t_error		parse_argv(t_info *info, int argc, char **argv);

// philo
t_error		seat_philos(t_info *info);
void		*philo_routine(void *arg);

// philo update
void		update_philo_state(t_philo *philo, int state);
void		update_philo_last_meal_start(t_philo *philo);
void		update_philo_meal_cnt(t_philo *philo);

// philo utils
void		print_philo_state(t_philo *philo, int state);
size_t		get_time_interval_us(struct timeval *start, struct timeval *now);
size_t		get_time_interval_ms(struct timeval *start, struct timeval *now);
t_bool		is_single_philo(t_philo *philo);
t_bool		is_done(t_philo *philo);
void		philo_unlock_mutexes(t_philo *philo);

// monitor
t_philo		*monitor_philos(t_philo *philos, t_shared_data *shared);


#endif