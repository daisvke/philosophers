/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 05:46:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/04 05:54:12 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_hold_fork(t_env *env, t_philo *philo, size_t side, int philo_id)
{
	size_t	fork_id;
	size_t	t;
	size_t	curr_time;

	if (env->philo_died == false)
	{
		fork_id = philo_id + side;
		fork_id = philo_id + side;
		if (philo_id == 0 && side == RIGHT)
			fork_id = env->philo_nbr - 1;
//printf("in fork and fork_id: %ld\n", fork_id);
//printf("in fork and side: %ld\n", side);
//printf("in fork and nbr: %ld,    id: %ld\n", env->philo_nbr, philo->id);
		if (pthread_mutex_lock(&env->forks[fork_id]) != SUCCESS)
		{
			env->errors[3] = true;
			return (ERROR);
		}
		if (ph_print_msg(env, philo, MSG_TAKE_FORK) == ERROR)
			return (ERROR);
		if (side == LEFT)
		{
			if (ph_gettime(env, &curr_time) == ERROR)
				return (ERROR);
			philo->last_meal_time = curr_time;
		}
	}
	return (SUCCESS);
}

int	ph_drop_forks(t_env *env, int philo_id)
{
	size_t	r_fork;
	size_t	l_fork;

	r_fork = philo_id - 1;
	if (philo_id == 0)
		r_fork = env->philo_nbr - 1;
	l_fork = philo_id;
	if (pthread_mutex_unlock(&env->forks[r_fork]) != SUCCESS \
		|| pthread_mutex_unlock(&env->forks[l_fork]) != SUCCESS)
	{
		env->errors[4] = true;
		return (ERROR);
	}
	return (SUCCESS);
}

int	ph_wait_until_eating(t_env *env, t_philo *philo)
{
	if (env->philo_died == false)
	{
		if (ph_print_msg(env, philo, MSG_EATING) == ERROR)
			return (ERROR);
		if (ph_usleep(env, env->time.eat) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int	ph_starve_if_solo_since_cannot_eat_with_one_fork(t_env *env)
{
	if (ph_usleep(env, env->time.eat) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_eat(t_env *env, t_philo *philo)
{
	size_t	philo_id;

	philo_id = philo->id;
	if (ph_hold_fork(env, philo, RIGHT, philo_id) == ERROR)
		return (ERROR);
	if (env->philo_nbr == 1)
	{
		if (ph_starve_if_solo_since_cannot_eat_with_one_fork(env) == ERROR)
			return (ERROR);
		return (SUCCESS);
	}
	if ( \
		ph_hold_fork(env, philo, LEFT, philo_id) == ERROR \
		|| ph_wait_until_eating(env, philo) == ERROR \
		|| ph_drop_forks(env, philo_id) == ERROR)
		return (ERROR);
	++philo->meal_count;
	if (env->philo_died == false)
		ph_check_if_philo_has_reached_meal_limit(env, philo);
	return (SUCCESS);
}
