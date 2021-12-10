/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_shortcuts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 01:17:36 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/10 09:04:12 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_lock_fork(t_env *env, size_t id)
{
	if (ph_pthread_mutex_lock(env, &env->forks[id]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_fork(t_env *env, size_t id)
{
	if (ph_pthread_mutex_unlock(env, &env->forks[id]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_lock_print(t_env *env)
{
	if (ph_pthread_mutex_lock(env, &env->locks[LK_LOCK_PRINT]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_print(t_env *env)
{
	if (ph_pthread_mutex_unlock(env, &env->locks[LK_LOCK_PRINT]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_lock_philo_died(t_env *env)
{
	if (ph_pthread_mutex_lock(env, &env->locks[LK_PHILO_DIED]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_philo_died(t_env *env)
{
	if (ph_pthread_mutex_unlock(env, &env->locks[LK_PHILO_DIED]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_lock_last_meal_time(t_env *env)
{
	if (ph_pthread_mutex_lock(env, &env->locks[LK_LAST_MEAL_TIME]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_last_meal_time(t_env *env)
{
	if (ph_pthread_mutex_unlock(env, &env->locks[LK_LAST_MEAL_TIME]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_lock_start_simulation(t_env *env)
{
	if (ph_pthread_mutex_lock(env, &env->locks[LK_START_SIMULATION]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_start_simulation(t_env *env)
{
	if (ph_pthread_mutex_unlock(env, &env->locks[LK_START_SIMULATION]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_lock_reached_meal_limit(t_env *env)
{
	if (ph_pthread_mutex_lock(env, &env->locks[LK_REACHED_MEAL_LIMIT]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_reached_meal_limit(t_env *env)
{
	if (ph_pthread_mutex_unlock(env, &env->locks[LK_REACHED_MEAL_LIMIT]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_lock_printf(t_env *env)
{
	if (ph_pthread_mutex_lock(env, &env->locks[LK_PRINTF]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_printf(t_env *env)
{
	if (ph_pthread_mutex_unlock(env, &env->locks[LK_PRINTF]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_lock_create_thread(t_env *env)
{
	if (ph_pthread_mutex_lock(env, &env->locks[LK_CREATE_THREAD]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_create_thread(t_env *env)
{
	if (ph_pthread_mutex_unlock(env, &env->locks[LK_CREATE_THREAD]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_lock_conditions(t_env *env)
{
	if (ph_lock_reached_meal_limit(env) == ERROR \
		|| ph_lock_philo_died(env) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_conditions(t_env *env)
{
	if (ph_unlock_philo_died(env) == ERROR \
		|| ph_unlock_reached_meal_limit(env) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_lock_conditions_2(t_env *env)
{
	if (ph_lock_philo_died(env) == ERROR \
		|| ph_lock_reached_meal_limit(env) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_conditions_2(t_env *env)
{
	if (ph_unlock_reached_meal_limit(env) == ERROR \
		|| ph_unlock_philo_died(env) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
