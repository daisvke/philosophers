/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_eating.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 05:46:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/10 00:37:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_starve_if_solo_since_cannot_eat_with_one_fork(t_env *env, t_philo *philo)
{
	size_t	fork_id;

	fork_id = 0;
	if (ph_pthread_mutex_unlock(env, &env->forks[fork_id]) == ERROR \
		|| ph_usleep(env, env->time.die) == ERROR)
		return (ERROR);
	pthread_mutex_lock(&env->locks[LK_PHILO_DIED]);
	env->philo_died = true;
	pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
	if (ph_print_msg(env, philo, MSG_DEATH) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_hold_a_fork(t_env *env, t_philo *philo, size_t id, bool next_fork)
{
	size_t	curr_time;

	if (ph_print_msg(env, philo, MSG_TAKE_FORK) == ERROR \
		|| pthread_mutex_lock(&env->forks[id]) == ERROR)
		return (ERROR);
	if (next_fork)
	{
		if (ph_gettime(env, &curr_time) == ERROR)
			return (ERROR);
		pthread_mutex_lock(&env->locks[LK_LAST_MEAL_TIME]);
		philo->last_meal_time = curr_time;
		pthread_mutex_unlock(&env->locks[LK_LAST_MEAL_TIME]);
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
	bool	error_occured;

	fork_1 = fork_ids[0];
	fork_2 = fork_ids[1];
	error_occured = false;
	if (pthread_mutex_unlock(&env->forks[fork_1]) != SUCCESS)
		error_occured = true;
	if (pthread_mutex_unlock(&env->forks[fork_2]) != SUCCESS)
		error_occured = true;
	if (error_occured == true)
		return (ERROR);
	return (SUCCESS);
}

int	ph_wait_until_eating(t_env *env, t_philo *philo, size_t *fork_ids)
{
	size_t	fork_1;
	size_t	fork_2;

	fork_1 = fork_ids[0];
	fork_2 = fork_ids[1];
	pthread_mutex_lock(&env->locks[LK_PHILO_DIED]);
	if (env->philo_died == false)
	{
		pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
		if (ph_print_msg(env, philo, MSG_EATING) == ERROR
			|| ph_usleep(env, env->time.eat) == ERROR)
		{
			pthread_mutex_unlock(&env->forks[fork_1]);
			pthread_mutex_unlock(&env->forks[fork_2]);
			return (ERROR);
		}
	}
	else
		pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
	return (SUCCESS);
}

void	ph_get_forks_id(t_philo *philo, size_t *fork_ids)
{
	t_env	*env;
	size_t	philo_id;
	size_t	hold_first;
	size_t	hold_next;

	env = philo->env;
	philo_id = philo->id;
	fork_ids[FK_RIGHT] = philo_id - 1;
	if (philo_id == 0)
		fork_ids[FK_RIGHT] = env->philo_nbr - 1;
	fork_ids[FK_LEFT] = philo_id;
	philo_id = philo->id;
	if (ph_is_impair(philo_id) == true)
	{
		hold_first = fork_ids[FK_LEFT];
		hold_next = fork_ids[FK_RIGHT];
	}
	else
	{
		hold_first = fork_ids[FK_RIGHT];
		hold_next = fork_ids[FK_LEFT];
	}
	fork_ids[0] = hold_first;
	fork_ids[1] = hold_next;
}

int	ph_is_eating(t_env *env, t_philo *philo)
{
	size_t	philo_id;
	size_t	fork_ids[2];

	philo_id = philo->id;
	ph_get_forks_id(philo, fork_ids);
	if (ph_hold_forks(env, philo, fork_ids) == ERROR \
		|| ph_wait_until_eating(env, philo, fork_ids) == ERROR \
		|| ph_drop_forks(env, fork_ids) == ERROR)
		return (ERROR);
	++philo->meal_count;
	pthread_mutex_lock(&env->locks[LK_PHILO_DIED]);
	if (env->philo_died == false)
	{
		pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
		ph_check_if_philo_has_reached_meal_limit(env, philo);
	}
	else
		pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
	return (SUCCESS);
}
