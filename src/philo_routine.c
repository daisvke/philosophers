/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 08:13:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/04 08:31:05 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_continue_diner(t_env *env, t_philo *philo)
{
	if (env->philo_died == false && philo->reached_meal_limit == false)
		return (true);
	return (false);
}

int	ph_sleep(t_env *env, t_philo *philo)
{
	if (env->philo_died == false)
	{
		if (ph_print_msg(env, philo, MSG_SLEEPING) == ERROR)
			return (ERROR);
		if (ph_usleep(env, env->time.sleep, philo->id) == ERROR)
			return (ERROR);
	}
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
//	printf("start routine for id: %d\n", id);
	if (ph_run_life_monitor(philo) == ERROR)
	{
		// msg failed? or inside functions
		return (NULL);
	}
	if (ph_gettime(env, &curr_time) == ERROR)
		return (NULL);
	philo->last_meal_time = curr_time;
	philo->monitor_on = true;
	while (ph_continue_diner(env, philo) == true)
	{
		if (ph_eat(env, philo) == ERROR \
			|| ph_sleep(env, philo) == ERROR)
			break ;
		if (ph_print_msg(env, philo, MSG_THINKING) == ERROR)
			return (NULL);
	}
	return (NULL);
}
