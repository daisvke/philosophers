/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:04:34 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/08 04:01:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_start_monitor(void *data)
{
	t_env	*env;
	t_philo	*philo;

	philo = (t_philo *)data;
	env = philo->env;
	pthread_mutex_lock(&env->locks[LK_PHILO_DIED]);
	pthread_mutex_lock(&env->locks[LK_REACHED_MEAL_LIMIT]);
	while (env->philo_died == false && philo->reached_meal_limit == false \
		&& env->error_occured_on_some_thread == false)
	{
		pthread_mutex_lock(&env->locks[LK_START_SIMULATION]);
		if (philo->start_simulation == true && ph_is_dead(env, philo) == true)
		{
			pthread_mutex_unlock(&env->locks[LK_START_SIMULATION]);
			pthread_mutex_unlock(&env->locks[LK_REACHED_MEAL_LIMIT]);
//			pthread_mutex_lock(&env->locks[LK_PHILO_DIED]);
			env->philo_died = true;
//			pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
			if (env->error_occured_on_some_thread == false)
				ph_print_msg(env, philo, MSG_DEATH);
			pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
			return (NULL);
		}
		pthread_mutex_unlock(&env->locks[LK_START_SIMULATION]);
	}
	pthread_mutex_unlock(&env->locks[LK_REACHED_MEAL_LIMIT]);
	pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
	return (NULL);
}

int	ph_run_life_monitor(t_philo *philo)
{
	t_env		*env;
	pthread_t	tid;

	env = philo->env;
	if (ph_pthread_create(env, &tid, ph_start_monitor, philo) == ERROR)
		return (ERROR);
	if (pthread_detach(tid) != SUCCESS)
	{
		env->errors[10] = true;
		return (ERROR);
	}
	return (SUCCESS);
}
