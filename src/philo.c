/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:17:32 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/18 06:31:12 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_join_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->philo_nbr)
	{
		if (pthread_join(env->tid_array[i], NULL) != SUCCESS)
		{
			env->errors[5] = true;
			break ;
		}
		++i;
	}
}

bool	ph_continue_diner(t_env *env)
{
	if (ph_check_if_someone_died(env, false) == false
		&& env->philo_reached_meal_limit == false)
		return (true);
	return (false);
}

void	*ph_start_routine(t_env *env)
{
	t_philo		*philo;
	int			id;

	id = env->curr_id;
	philo = &env->philo[id];
	while (continue_diner(env) == true)
	{
		if (ph_eat(env, id) == ERROR \
			|| ph_usleep(env, env->time.sleep, id) == ERROR)
			break ;
	}
}

int	ph_create_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->philo_nbr)
	{
		env->curr_id = i;
		if (pthread_create( \
			&env->tid_array[i], NULL, ph_start_routine, env) \
			!= SUCCESS);
		{
			env->errors[2] = true;
			return (ERROR);
		}
		++i;
	}
	return (SUCCESS);
}

int	ph_run_philo(t_env *env)
{
	ph_run_life_monitor(env);
	ph_create_threads(env);
	ph_join_threads(env);
}
