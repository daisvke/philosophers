/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:04:34 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/04 08:32:20 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_start_monitor(void *data)
{
	t_env	*env;
	t_philo	*philo;

	philo = (t_philo *)data;
	env = philo->env;
	while (env->philo_died == false && philo->reached_meal_limit == false
		&& env->error_occured_on_some_thread == false)
	if (philo->monitor_on == true && ph_is_dead(env, philo) == true)
	{
		env->philo_died = true;
		if (env->error_occured_on_some_thread == false)
			ph_print_msg(env, philo, MSG_DEATH);
		return (NULL);
	}
	return (NULL);
}

int	ph_run_life_monitor(t_philo *philo)
{
	t_env		*env;
	pthread_t	tid;

	env = philo->env;
	if (ph_pthread_create(env, &tid, ph_start_monitor, philo) != SUCCESS)
		return (ERROR);
	if (pthread_detach(tid) != SUCCESS)
	{
		env->errors[10] = true;
		return (ERROR);
	}
	return (SUCCESS);
}
