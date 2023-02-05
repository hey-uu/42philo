/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyukim <hyeyukim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:50:04 by hyeyukim          #+#    #+#             */
/*   Updated: 2023/02/05 17:24:33 by hyeyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"

static t_error	check_args_number(int num)
{
	t_errcode	errcode;

	errcode = ERRCODE_NONE;
	if (num < 4)
		errcode = ERRCODE_FEW_ARGS;
	else if (num > 5)
		errcode = ERRCODE_TOO_MANY_ARGS;
	if (errcode == ERRCODE_NONE)
		return (ERROR_NONE);
	print_err_msg(errcode);
	return (ERROR);
}

static t_errcode	store_int_arg(int *iarg, char *arg)
{
	long	num;

	while ((*arg >= '\t' && *arg <= '\r') || *arg == ' ')
		arg++;
	if (*arg == '-')
		return (ERRCODE_NOT_POSITIVE);
	if (*arg == '+')
		arg++;
	num = 0;
	while (*arg >= '0' && *arg <= '9')
	{
		num = num * 10 + *arg - '0';
		if (num > INT_MAX)
			return (ERRCODE_OVER_INTMAX);
		arg++;
	}
	if (*arg && !(*arg >= '0' && *arg <= '9'))
		return (ERRCODE_NUMERIC_REQUIRED);
	*iarg = (int)num;
	return (ERRCODE_NONE);
}

static t_error	str_to_int(int *iarg, char *arg)
{
	t_errcode	errcode;

	if (!arg)
	{
		*iarg = NO_OPT;
		return (ERROR_NONE);
	}
	errcode = store_int_arg(iarg, arg);
	if (errcode == ERRCODE_NONE)
		return (ERROR_NONE);
	print_err_msg(errcode);
	return (ERROR);
}

t_error	parse_argv(t_info *info, int argc, char **argv)
{
	if (check_args_number(argc - 1) == ERROR)
		return (ERROR);
	if (str_to_int(&info->shared.philo_num, argv[1]) == ERROR)
		return (ERROR);
	if (str_to_int((int *)&info->shared.time_to_die, argv[2]) == ERROR)
		return (ERROR);
	if (str_to_int((int *)&info->shared.time_to_eat, argv[3]) == ERROR)
		return (ERROR);
	if (str_to_int((int *)&info->shared.time_to_sleep, argv[4]) == ERROR)
		return (ERROR);
	if (str_to_int(&info->shared.must_eat_num, argv[5]) == ERROR)
		return (ERROR);
	return (ERROR_NONE);
}
