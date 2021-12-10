/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 08:13:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/10 03:12:05 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_continue_diner(t_env *env, t_philo *philo)
{
	ph_lock_philo_died(env);
	ph_lock_reached_meal_limit(env);
	if (env->philo_died == false && philo->reached_meal_limit == false \
		&& env->error_occured_on_some_thread == false)
	{
		ph_unlock_reached_meal_limit(env);
		ph_unlock_philo_died(env);
		return (true);
	}
	ph_unlock_reached_meal_limit(env);
	ph_unlock_philo_died(env);
	return (false);
}

int	ph_is_sleeping(t_env *env, t_philo *philo)
{
	ph_lock_philo_died(env);
	if (env->philo_died == false)
	{
		ph_unlock_philo_died(env);
		if (ph_print_msg(env, philo, MSG_SLEEPING) == ERROR)
			return (ERROR);
		if (ph_usleep(env, env->time.sleep) == ERROR)
			return (ERROR);
	}
	else
		ph_unlock_philo_died(env);
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
	t_env		*env;
	t_philo		*philo;
	pthread_t	monitor_tid;
	size_t		id;
	size_t		curr_time;

	philo = (t_philo *)data;
	env = philo->env;
	id = philo->id;
	if (ph_run_life_monitor(philo, &monitor_tid) == ERROR)
		return (NULL);
	if (ph_gettime(env, &curr_time) == ERROR)
		return (NULL);
	ph_lock_last_meal_time(env);
	philo->last_meal_time = curr_time;
	ph_unlock_last_meal_time(env);
	ph_lock_start_simulation(env);
	philo->start_simulation = true;
	ph_unlock_start_simulation(env);
	while (ph_continue_diner(env, philo) == true)
	{
		if (ph_is_eating(env, philo) == ERROR \
			|| ph_is_sleeping(env, philo) == ERROR \
			|| ph_is_thinking(env, philo) == ERROR)
			break ;
	}
	ph_pthread_join(env, monitor_tid);
	return (NULL);
}
