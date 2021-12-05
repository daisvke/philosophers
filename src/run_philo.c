/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:17:32 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/04 08:14:07 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_join_threads(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->philo_nbr)
	{
		if (ph_pthread_join(env, env->threads[i]) == ERROR)
			break ;
		++i;
	}
}

int	ph_init_start_time(t_env *env)
{
	size_t		start_time;

	if (ph_gettime(env, &start_time) == ERROR)
		return (ERROR);
	env->time.start = start_time;
	return (SUCCESS);
}

int	ph_sleep_to_avoid_initial_conflict_over_forks(t_env *env)
{
	if (ph_usleep(env, 10) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	ph_spawn_philosophers(t_env *env, t_philo *philo_arr)
{
	size_t	i;

	if (ph_init_start_time(env) == ERROR)
		return ;
	i = 0;
	while (i < env->philo_nbr)
	{
		philo_arr[i].id = i;
		if (ph_pthread_create( \
			env, &env->threads[i], ph_start_routine, &philo_arr[i]) != SUCCESS)
			return ;
		if (ph_sleep_to_avoid_initial_conflict_over_forks(env) == ERROR)
			return ;
		++i;
	}
}

void	ph_run_philo(t_env *env, t_philo *philo_arr)
{
	ph_spawn_philosophers(env, philo_arr);
	ph_join_threads(env);
}
