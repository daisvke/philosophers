/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:04:34 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/09 05:18:45 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_start_monitor(void *data)
{
	t_env	*env;
	t_philo	*philo;

	philo = (t_philo *)data;
	env = philo->env;
	
//	bool	went_inside_loop;
//	went_inside_loop = false;
/*	
	pthread_mutex_lock(&env->locks[LK_PHILO_DIED]);
	pthread_mutex_lock(&env->locks[LK_REACHED_MEAL_LIMIT]);
	while (env->philo_died == false && philo->reached_meal_limit == false \
			&& env->error_occured_on_some_thread == false)
	{
		went_inside_loop = true;
		pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
		pthread_mutex_unlock(&env->locks[LK_REACHED_MEAL_LIMIT]);
		pthread_mutex_lock(&env->locks[LK_START_SIMULATION]);
		if (philo->start_simulation == true && ph_is_dead(env, philo) == true)
		{
			pthread_mutex_unlock(&env->locks[LK_START_SIMULATION]);

			pthread_mutex_lock(&env->locks[LK_PHILO_DIED]);
			env->philo_died = true;
			pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
			if (env->error_occured_on_some_thread == false)
				ph_print_msg(env, philo, MSG_DEATH);
			return (NULL);
		}
		pthread_mutex_unlock(&env->locks[LK_START_SIMULATION]);
		//	pthread_mutex_unlock(&env->locks[LK_START_SIMULATION]);
	}
	if (went_inside_loop == false) 
	{
		pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
		pthread_mutex_unlock(&env->locks[LK_REACHED_MEAL_LIMIT]);
	}
*/

/*
	if (env->philo_died == false && philo->reached_meal_limit == false \
		&& env->error_occured_on_some_thread == false)
	{
		pthread_mutex_unlock(&env->locks[LK_REACHED_MEAL_LIMIT]);
		pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);*/
		
/*
		pthread_mutex_lock(&env->locks[LK_PHILO_DIED]);
	pthread_mutex_lock(&env->locks[LK_REACHED_MEAL_LIMIT]);*/
	//	while (env->philo_died == false && env->)
		while (pthread_mutex_lock(&env->locks[LK_PHILO_DIED]) == SUCCESS \
			&& pthread_mutex_lock(&env->locks[LK_REACHED_MEAL_LIMIT]) == SUCCESS \
			&& env->philo_died == false && philo->reached_meal_limit == false \
		&& env->error_occured_on_some_thread == false)
		{
			pthread_mutex_unlock(&env->locks[LK_REACHED_MEAL_LIMIT]);
			pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
		//	went_inside_loop = true;
				pthread_mutex_lock(&env->locks[LK_START_SIMULATION]);
				if (philo->start_simulation == true && ph_is_dead(env, philo) == true)
				{
					pthread_mutex_unlock(&env->locks[LK_START_SIMULATION]);
					pthread_mutex_lock(&env->locks[LK_PHILO_DIED]);
					env->philo_died = true;
					pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
					if (env->error_occured_on_some_thread == false)
						ph_print_msg(env, philo, MSG_DEATH);
					return (NULL);
				}
				pthread_mutex_unlock(&env->locks[LK_START_SIMULATION]);
//	pthread_mutex_lock(&env->locks[LK_REACHED_MEAL_LIMIT]);
//		pthread_mutex_lock(&env->locks[LK_PHILO_DIED]);
		
//	pthread_mutex_lock(&env->locks[LK_REACHED_MEAL_LIMIT]);
		}
		pthread_mutex_unlock(&env->locks[LK_REACHED_MEAL_LIMIT]);
		pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
		/*
	}
	else
	{
		pthread_mutex_unlock(&env->locks[LK_REACHED_MEAL_LIMIT]);
		pthread_mutex_unlock(&env->locks[LK_PHILO_DIED]);
	}*/
	return (NULL);
}

int	ph_run_life_monitor(t_philo *philo)
{
	t_env		*env;

	env = philo->env;
	if (ph_pthread_create(env, &env->monitor_tid, ph_start_monitor, philo) == ERROR)
		return (ERROR);
/*	if (pthread_detach(tid) != SUCCESS)
	{
		env->errors[10] = true;
		return (ERROR);
	}*/
	return (SUCCESS);
}
