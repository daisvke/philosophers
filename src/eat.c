/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 05:46:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/18 06:35:22 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_hold_fork(t_env *env, int philo_id, int side)
{
	int	fork_id;

	if (env->philo_died == false)
	{
		fork_id = philo_id + side;
		if (pthread_mutex_lock(env->forks[fork_id]) != SUCCESS)
		{
			env->errors[3];
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	ph_drop_forks(t_env *env, int philo_id)
{
	int	r_fork;
	int	l_fork;

	if (env->philo_died == false)
	{
		r_fork = philo_id - 1;
		l_fork = philo_id + 1;
		if (pthread_mutex_unlock(env->forks[r_fork]) != SUCCESS \
			|| pthread_mutex_unlock(env->forks[l_fork]) != SUCCESS)
		{
			env->errors[4];
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	ph_wait_until_eating(void)
{
	if (ph_usleep(env, env->time.eat) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_eat(t_env *env, int philo_id)
{
	t_philo	*philo;

	if (ph_hold_fork(env, RIGHT, philo_id) == ERROR \
		|| ph_hold_fork(env, LEFT, philo_id) == ERROR \
		|| ph_wait_until_eating();
		|| ph_drop_forks(env) == ERROR)
		return (ERROR);
	philo = &env->philo[philo_id];
	++philo.meal_count;
	ph_check_if_philo_has_reached_meal_limit(env, philo_id);
	return (SUCCESS);
}
