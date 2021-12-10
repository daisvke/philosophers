/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 08:13:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/10 05:10:55 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_continue_diner(t_env *env, t_philo *philo)
{
	if (ph_lock_conditions_2(env) == ERROR)
		return (false);
	if (\
		env->philo_died == false \
		&& philo->reached_meal_limit == false \
		&& env->error_occured_on_some_thread == false \
		)
	{
		if (ph_unlock_conditions_2(env) == ERROR)
			return (false);
		return (true);
	}
	if (ph_unlock_conditions_2(env) == ERROR)
		return (NULL);
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

int	ph_notify_simulation_has_started_and_set_the_last_meal_time(\
	t_env *env, t_philo *philo)
{
	size_t		curr_time;

	if (ph_gettime(env, &curr_time) == ERROR)
		return (ERROR);
	if (ph_lock_last_meal_time(env) == ERROR)
		return (ERROR);
	philo->last_meal_time = curr_time;
	if (ph_unlock_last_meal_time(env) == ERROR)
		return (ERROR);
	if (ph_lock_start_simulation(env) == ERROR)
		return (ERROR);
	philo->start_simulation = true;
	if (ph_unlock_start_simulation(env) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	*ph_start_routine_philo(void *data)
{
	t_env		*env;
	t_philo		*philo;
	pthread_t	monitor_tid;
	size_t		id;

	philo = (t_philo *)data;
	env = philo->env;
	id = philo->id;
	if (ph_run_life_monitor(philo, &monitor_tid) == ERROR)
		return (NULL);
	if (ph_notify_simulation_has_started_and_set_the_last_meal_time(\
		env, philo) == ERROR)
		return (NULL);
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
