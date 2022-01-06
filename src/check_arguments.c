/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 04:12:37 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/01/06 04:21:14 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_check_if_args_are_numbers(t_env *env, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ph_is_numeric(argv[i]) == false)
		{
			env->errors[8] = true;
			return (ERROR);
		}
		++i;
	}
	return (SUCCESS);
}

bool	ph_check_if_args_contain_signs(t_env *env, int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '-' || argv[i][j] == '+')
			{
				env->errors[13] = true;
				return (ERROR);
			}
			++j;
		}
		++i;
	}
	return (SUCCESS);
}

bool	ph_check_if_args_are_too_long(t_env *env, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ph_strlen(argv[i]) > 10)
		{
			env->errors[14] = true;
			return (ERROR);
		}
		++i;
	}
	return (SUCCESS);
}

int	ph_assign_args_in_env(t_env *env, int argc, char *argv[])
{
	bool	error;

	error = false;
	env->philo_nbr = ph_convert_str_to_int(env, argv[1], &error);
	env->time.die = ph_convert_str_to_int(env, argv[2], &error);
	env->time.eat = ph_convert_str_to_int(env, argv[3], &error);
	env->time.sleep = ph_convert_str_to_int(env, argv[4], &error);
	if (argc > 5)
		env->meal_limit = ph_convert_str_to_int(env, argv[5], &error);
	return (error);
}

bool	ph_check_args(t_env *env, int argc, char *argv[])
{
	size_t	error;

	if (argc >= 5 && argc <= 6)
	{
		error = 0;
		error += ph_check_if_args_are_numbers(env, argc, argv);
		error += ph_check_if_args_contain_signs(env, argc, argv);
		error += ph_check_if_args_are_too_long(env, argc, argv);
		error += ph_assign_args_in_env(env, argc, argv);
		if (error > 0)
			return (ERROR);
		return (SUCCESS);
	}
	env->errors[0] = true;
	return (ERROR);
}
