/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:16:24 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/06 11:27:47 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_check_if_args_are_numbers(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ph_is_numeric(argv[i]) == false)
			return (false);
		++i;
	}
	return (true);
}

bool	ph_check_args(t_env *env, int argc, char *argv[])
{
	bool	found_error;

	found_error = false;
	if (argc < 5)
	{	
		env->errors[0] = true;
		found_error = true;
	}
	if (ph_check_if_args_are_numbers(argc, argv) == false)
	{
		env->errors[8] = true;
		found_error = true;
	}
	if (found_error == true)
		return (ERROR);
	return (OK);
}

int	main(int argc, char *argv[])
{
	t_env	env;
	t_philo	*philo_arr;

	ph_init_errors(&env);
	if (ph_check_args(&env, argc, argv) != ERROR)
	{
		if (ph_init_env(&env, argc, argv, &philo_arr) != ERROR)
			ph_run_philo(&env, philo_arr);
		ph_free_arrays(&env, philo_arr);
	}
	return (ph_print_errors_if_any_and_exit(env));
}
