/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:16:24 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/21 11:12:01 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_is_numeric(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '+' && str[i] != '-' \
			&& (str[i] < '0' || str[i] > '9'))
			return (false);
		++i;
	}
	return (true);
}

bool	ph_check_if_args_are_numbers(int argc, char *argv[])
{
	size_t	i;

	i = 1;
	while (i < argc)
	{
		if (ph_is_numeric(argv[i]) == false)
			return (false);
		++i;
	}
	return (true);
}

bool	ph_check_args(int argc, char *argv[])
{
	if (argc < 5 || ph_check_if_args_are_numbers(argc, argv) == false)
		return (ERROR);
	return (OK);
}

void	ph_free_arrays(t_env *env, t_philo *philo_arr)
{
	env->threads = ph_free(env->threads);
	env->forks = ph_free(env->forks);
	philo_arr = ph_free(philo_arr);
}

int	main(int argc, char *argv[])
{
	t_env	env;
	t_philo	*philo_arr;
	int		res;
	
	res = 0;
	ph_init_errors(&env);
	if (ph_check_args(argc, argv) != ERROR)
	{
		if (ph_init_env(&env, argc, argv, &philo_arr) != ERROR)
			res = ph_run_philo(&env, philo_arr);
		ph_free_arrays(&env, philo_arr);
	}
	return (res || ph_check_errors(env));
}
