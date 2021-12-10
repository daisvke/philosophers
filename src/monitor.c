/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:04:34 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/10 05:02:52 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_continue_monitor(t_env *env, t_philo *philo)
{
	if (\
		ph_lock_conditions_2(env) == SUCCESS \
		&& env->philo_died == false \
		&& philo->reached_meal_limit == false \
		&& env->error_occured_on_some_thread == false \
		)
		return (true);
	return (false);
}

void	ph_notify_of_the_death_of_a_philosopher(t_env *env, t_philo *philo)
{
	ph_lock_philo_died(env);
	env->philo_died = true;
	ph_unlock_philo_died(env);
	if (env->error_occured_on_some_thread == false)
		ph_print_msg(env, philo, MSG_DEATH);
}

void	*ph_start_routine_monitor(void *data)
{
	t_env	*env;
	t_philo	*philo;

	philo = (t_philo *)data;
	env = philo->env;
	while (ph_continue_monitor(env, philo) == true)
	{
		if (ph_unlock_conditions(env) == ERROR
			|| ph_lock_start_simulation(env) == ERROR)
			return (NULL);
		if (philo->start_simulation == true && ph_is_dead(env, philo) == true)
		{
			ph_unlock_start_simulation(env);
			ph_notify_of_the_death_of_a_philosopher(env, philo);
			return (NULL);
		}
		if (ph_unlock_start_simulation(env) == ERROR)
			return (NULL);
	}
	ph_unlock_conditions(env);
	return (NULL);
}

int	ph_run_life_monitor(t_philo *philo, pthread_t *monitor_tid)
{
	t_env		*env;

	env = philo->env;
	if (ph_pthread_create(\
		env, monitor_tid, ph_start_routine_monitor, philo \
		) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
