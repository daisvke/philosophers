/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:35:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/24 03:44:45 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_init_errors(t_env *env)
{
	int	i;

	i = 0;
	while (i <= ERR_LIMIT)
	{
		env->errors[i] = false;
		++i;
	}
}

int	ph_init_tid_array(t_env *env)
{
	int	philo_nbr;

	philo_nbr = env->philo_nbr;
	if (!malloc(env->tid_arr, philo_nbr, sizeof(pthread_t)))
		return (ERROR);
	memset(env->tid_arr, 0, philo_nbr);
	return (SUCCESS);
}

int	ph_init_fork_array(t_env *env)
{
	int	philo_nbr;

	philo_nbr = env->philo_nbr;
	if (!malloc(env->forks, philo_nbr, sizeof(pthread_mutex_t)))
		return (ERROR);
	memset(env->forks, 0, philo_nbr);
	return (SUCCESS);
}

int	ph_init_env(t_env *env, char *argv[])
{
	memset(env, 0, sizeof(env));
	env->philo_nbr = ph_convert_str_to_int(argv[1]);
	env->die_time = ph_convert_str_to_int(argv[2]);
	env->eat_time = ph_convert_str_to_int(argv[3]);
	env->sleep_time = ph_convert_str_to_int(argv[4]);
	if (argc > 5)
		env->eat_limit = ph_convert_str_to_int(argv[5]);
	if (ph_init_tid_array(env) == ERROR || ph_init_fork_array(env) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
