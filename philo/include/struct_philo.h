/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_philo.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:39:53 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/05 21:15:53 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_PHILO_H
# define STRUCT_PHILO_H

/*----------------------------- STANDARD HEADERS -----------------------------*/

# include <pthread.h>
# include <sys/time.h>

/*-------------------------- DEFINE MACRO CONSTANTS --------------------------*/

// argument option
# define NO_OPT -1

// philosopher messages
# define MSG_GETTING_READY				"is getting ready"
# define MSG_NOW_READY					"is on ready"
# define MSG_THINKING					"is thinking"
# define MSG_GETTING_FORK				"has taken a fork"
# define MSG_EATING						"is eating"
# define MSG_SLEEPING					"is sleeping"
# define MSG_DEAD						"died"

/*----------------------------------- ENUM -----------------------------------*/

enum e_bool
{
	FALSE,
	TRUE
};

enum	e_done
{
	CONTINUE,
	DONE
};

enum e_philo_state
{
	GET_READY,
	NOW_READY,
	PICK_UP_LEFT_FORK,
	PICK_UP_RIGHT_FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
};

/*-------------------------------- TYPE DEFINE -------------------------------*/

typedef enum e_bool			t_bool;
typedef enum e_done			t_done;

/*--------------------------- STRUCT DECLARATIONS ----------------------------*/

typedef struct s_shared_data
{
	pthread_mutex_t	monitor_lock;
	pthread_mutex_t	print_lock;
	t_bool			is_done;
	int				philo_num;
	int				done_philos;
	struct timeval	start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				must_eat_num;
}	t_shared_data;

typedef struct s_philo_time
{
	struct timeval	last_meal_start;
	struct timeval	last_meal_end;
	struct timeval	now;
}	t_philo_time;

typedef struct s_philo
{
	pthread_t		tid;
	int				id;
	int				state;
	int				eat_cnt;
	pthread_mutex_t	*time_lock;
	pthread_mutex_t	*state_lock;
	pthread_mutex_t	*eat_num_lock;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	t_philo_time	time;
	t_shared_data	*shared;
}	t_philo;

typedef struct s_info
{
	t_philo			*philos;
	pthread_mutex_t	*time_locks;
	pthread_mutex_t	*state_locks;
	pthread_mutex_t	*eat_num_locks;
	pthread_mutex_t	*forks;
	t_shared_data	shared;
}	t_info;

#endif