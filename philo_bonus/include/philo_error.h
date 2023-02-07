/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:45:32 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/05 17:42:41 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ERROR_H
# define PHILO_ERROR_H

/*-------------------------- DEFINE MACRO CONSTANTS --------------------------*/

// error messages
# define ERRMSG_FEW_ARGS				"PHILO ERROR: Few arguments."
# define ERRMSG_TOO_MANY_ARGS 			"PHILO ERROR: Too many arguments."
# define ERRMSG_NOT_POSITIVE			"PHILO ERROR: Not positive integer."
# define ERRMSG_OVER_INTMAX				"PHILO ERROR: Over INTMAX."
# define ERRMSG_NUMERIC_REQUIRED		"\
PHILO ERROR: Numeric argument required."
# define ERRMSG_FAILED_MUTEX_INIT		"PHILO ERROR: Failed to init mutex."
# define ERRMSG_FAILED_MALLOC			"PHILO ERROR: Failed to malloc memory."
# define ERRMSG_NO_PHILO				"PHILO ERROR: No philosopher exists."
# define ERRMSG_THREAD_CREATE_FAILED	"\
PHILO ERROR: Failed to create a new thread."
# define ERRMSG_THREAD_JOIN_FAILED		"PHILO ERROR: Failed to join a thread."

/*----------------------------------- ENUM -----------------------------------*/

enum e_error
{
	ERROR_NONE,
	ERROR
};

enum e_errcode
{
	ERRCODE_NONE,
	ERRCODE_FEW_ARGS,
	ERRCODE_TOO_MANY_ARGS,
	ERRCODE_NOT_POSITIVE,
	ERRCODE_OVER_INTMAX,
	ERRCODE_NUMERIC_REQUIRED,
	ERRCODE_FAILED_MUTEX_INIT,
	ERRCODE_FAILED_MALLOC,
	ERRCODE_NO_PHILO,
	ERRCODE_THREAD_CREATE_FAILED,
	ERRCODE_THREAD_JOIN_FAILED
};

enum e_errlev
{
	ERRLEV_NEW_FORKS,
	ERRLEV_NEW_STATE_LOCKS,
	ERRLEV_NEW_TIME_LOCKS,
	ERRLEV_NEW_EAT_NUM_LOCKS,
	ERRLEV_NEW_PHILOS
};

/*-------------------------------- TYPE DEFINE -------------------------------*/

typedef enum e_error		t_error;
typedef enum e_errcode		t_errcode;
typedef enum e_errlev		t_errlev;

#endif