/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_eating.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 05:46:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/01/06 04:03:38 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_hold_a_fork(t_env *env, t_philo *philo, size_t id, bool next_fork)
{
	size_t	curr_time;

	if (ph_lock_fork(env, id) == ERROR \
		|| ph_print_msg(env, philo, MSG_TAKE_FORK) == ERROR)
		return (ERROR);
	if (next_fork)
	{
		if (ph_gettime(env, &curr_time) == ERROR \
			|| ph_lock_last_meal_time(env) == ERROR)
			return (ERROR);
		philo->last_meal_time = curr_time;
		if (ph_unlock_last_meal_time(env) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int	ph_hold_forks(t_env *env, t_philo *philo, size_t *fork_ids)
{
	size_t	fork_1;
	size_t	fork_2;

	fork_1 = fork_ids[0];
	fork_2 = fork_ids[1];
	ph_hold_a_fork(env, philo, fork_1, false);
	if (env->philo_nbr == 1)
	{
		if (ph_starve_if_solo_since_cannot_eat_with_one_fork(\
			env, philo) == ERROR)
			return (ERROR);
		return (ERROR);
	}
	ph_hold_a_fork(env, philo, fork_2, true);
	return (SUCCESS);
}

int	ph_drop_forks(t_env *env, size_t *fork_ids)
{
	size_t	fork_1;
	size_t	fork_2;

	fork_1 = fork_ids[0];
	fork_2 = fork_ids[1];
	if (ph_unlock_fork(env, fork_1) == ERROR \
		|| ph_unlock_fork(env, fork_2) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_wait_until_eating(t_env *env, t_philo *philo, size_t *fork_ids)
{
	if (ph_lock_philo_died(env) == ERROR)
		return (ERROR);
	if (env->philo_died == false)
	{
		if (ph_unlock_philo_died(env) == ERROR \
			|| ph_print_msg(env, philo, MSG_EATING) == ERROR \
			|| ph_usleep(env, env->time.eat) == ERROR)
		{
			ph_drop_forks(env, fork_ids);
			return (ERROR);
		}
	}
	else
		if (ph_unlock_philo_died(env) == ERROR)
			return (ERROR);
	return (SUCCESS);
}

int	ph_is_eating(t_env *env, t_philo *philo)
{
	size_t	fork_ids[2];

	ph_get_forks_id(philo, fork_ids);
	if (ph_hold_forks(env, philo, fork_ids) == ERROR \
		|| ph_wait_until_eating(env, philo, fork_ids) == ERROR \
		|| ph_drop_forks(env, fork_ids) == ERROR)
		return (ERROR);
	++philo->meal_count;
	if (ph_lock_philo_died(env) == ERROR)
		return (ERROR);
	if (env->philo_died == false)
	{
		if (ph_unlock_philo_died(env) == ERROR)
			return (ERROR);
		ph_check_if_philo_has_reached_meal_limit(env, philo);
	}
	else
	{
		if (ph_unlock_philo_died(env) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
