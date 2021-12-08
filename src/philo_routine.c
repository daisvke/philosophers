/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 08:13:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/08 04:02:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_continue_diner(t_env *env, t_philo *philo)
{
//	pthread_mutex_lock(&env->locks[LK_END_CONDITIONS]);
	pthread_mutex_lock(&env->locks[LK_PHILO_DIED]);
	if (env->philo_died == false && philo->reached_meal_limit == false \
		&& env->error_occured_on_some_thread == false)
	{
	pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
//	pthread_mutex_unlock(&env->locks[LK_END_CONDITIONS]);
		return (true);
	}
	pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
//	pthread_mutex_unlock(&env->locks[LK_END_CONDITIONS]);
	return (false);
}

int	ph_is_sleeping(t_env *env, t_philo *philo)
{
	if (env->philo_died == false)
	{
		if (ph_print_msg(env, philo, MSG_SLEEPING) == ERROR)
			return (ERROR);
		if (ph_usleep(env, env->time.sleep) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int	ph_is_thinking(t_env *env, t_philo *philo)
{
	if (ph_print_msg(env, philo, MSG_THINKING) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	*ph_start_routine(void *data)
{
	t_env	*env;
	t_philo	*philo;
	size_t	id;
	size_t	curr_time;

	philo = (t_philo *)data;
	env = philo->env;
	id = philo->id;
	if (ph_run_life_monitor(philo) == ERROR)
		return (NULL);
	if (ph_gettime(env, &curr_time) == ERROR)
		return (NULL);
	pthread_mutex_lock(&env->locks[LK_LAST_MEAL_TIME]);
	philo->last_meal_time = curr_time;
	pthread_mutex_unlock(&env->locks[LK_LAST_MEAL_TIME]);
	pthread_mutex_lock(&env->locks[LK_START_SIMULATION]);
	philo->start_simulation = true;
	pthread_mutex_unlock(&env->locks[LK_START_SIMULATION]);
	while (ph_continue_diner(env, philo) == true)
	{
		if (ph_is_eating(env, philo) == ERROR \
			|| ph_is_sleeping(env, philo) == ERROR \
			|| ph_is_thinking(env, philo) == ERROR)
			break ;
	}
	return (NULL);
}
