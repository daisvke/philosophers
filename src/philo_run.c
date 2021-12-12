/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:17:32 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/12 03:35:01 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_join_threads(t_env *env, size_t i_max)
{
	size_t	i;

	i = 0;
	while (i < i_max)
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

int	ph_sleep_to_synchronize_pairs_and_impairs(t_env *env)
{
	if (ph_usleep(env, 1) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_spawn_philosophers(t_env *env, t_philo *philo_arr, size_t *i)
{
	if (ph_init_start_time(env) == ERROR)
		return (ERROR);
	*i = 0;
	while (*i < env->philo_nbr)
	{
		if (ph_is_impair(*i + 1) == false)
		{
			if (ph_sleep_to_synchronize_pairs_and_impairs(env) == ERROR)
				return (ERROR);
		}
		philo_arr[*i].id = *i;
		if (ph_pthread_create(\
			env, &env->threads[*i], \
			ph_start_routine_philo, \
			&philo_arr[*i]) != SUCCESS)
			return (ERROR);
		*i += 1;
	}
	return (SUCCESS);
}

void	ph_run_philo(t_env *env, t_philo *philo_arr)
{
	size_t	index_where_loop_stopped;

	if (ph_spawn_philosophers(env, philo_arr, &index_where_loop_stopped) \
		== ERROR)
		return ;
	ph_join_threads(env, index_where_loop_stopped);
}
