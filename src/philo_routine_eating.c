/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_eating.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 05:46:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/07 21:22:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_hold_fork(t_env *env, t_philo *philo, int side, int philo_id)
{
	size_t	fork_id;
	size_t	curr_time;

	if (env->philo_died == false)
	{
		fork_id = philo_id + side;
		if (philo_id == 0 && side == RIGHT)
			fork_id = env->philo_nbr - 1;
		if (ph_pthread_mutex_lock(env, &env->forks[fork_id]) == ERROR \
			|| ph_print_msg(env, philo, MSG_TAKE_FORK) == ERROR)
			return (ERROR);
		if (side == LEFT)
		{
			if (ph_gettime(env, &curr_time) == ERROR)
				return (ERROR);
			pthread_mutex_lock(&env->locks[LK_LAST_MEAL_TIME]);
			philo->last_meal_time = curr_time;
			pthread_mutex_unlock(&env->locks[LK_LAST_MEAL_TIME]);
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
	if (ph_pthread_mutex_unlock(env, &env->forks[r_fork]) == ERROR \
		|| ph_pthread_mutex_unlock(env, &env->forks[l_fork]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_wait_until_eating(t_env *env, t_philo *philo)
{
//	if (env->philo_died == false)
//	{
		if (ph_print_msg(env, philo, MSG_EATING) == ERROR)
			return (ERROR);
		if (ph_usleep(env, env->time.eat) == ERROR)
			return (ERROR);
//	}
	return (SUCCESS);
}

int	ph_starve_if_solo_since_cannot_eat_with_one_fork(t_env *env, t_philo *philo)
{
	if (ph_usleep(env, env->time.die) == ERROR)
		return (ERROR);
	pthread_mutex_lock(&env->locks[LK_PHILO_DIED]);
	env->philo_died = true;
	pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
	if (ph_print_msg(env, philo, MSG_DEATH) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_is_eating(t_env *env, t_philo *philo)
{
	size_t	philo_id;

	philo_id = philo->id;
	if (ph_hold_fork(env, philo, RIGHT, philo_id) == ERROR)
		return (ERROR);
	if (env->philo_nbr == 1)
	{
		if (ph_starve_if_solo_since_cannot_eat_with_one_fork(\
			env, philo) == ERROR)
			return (ERROR);
		return (SUCCESS);
	}
	if (ph_hold_fork(env, philo, LEFT, philo_id) == ERROR \
		|| ph_wait_until_eating(env, philo) == ERROR \
		|| ph_drop_forks(env, philo_id) == ERROR)
		return (ERROR);
	++philo->meal_count;
	if (env->philo_died == false)
		ph_check_if_philo_has_reached_meal_limit(env, philo);
	return (SUCCESS);
}
