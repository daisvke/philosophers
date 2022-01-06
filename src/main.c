/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:16:24 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/01/06 04:18:02 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_init_errors(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < ERR_LIMIT)
		env->errors[i++] = false;
}

int	main(int argc, char *argv[])
{
	t_env	env;
	t_philo	*philo_arr;

	memset(&env, 0, sizeof(t_env));
	ph_init_errors(&env);
	if (ph_check_args(&env, argc, argv) != ERROR)
	{
		if (ph_init_env(&env, &philo_arr) != ERROR)
			ph_run_philo(&env, philo_arr);
		ph_clean_arrays(&env, philo_arr);
	}
	return (ph_print_errors_if_any_and_exit(env));
}
