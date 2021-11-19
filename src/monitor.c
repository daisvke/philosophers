/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:04:34 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/19 04:48:28 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_start_monitor(void *data)
{
	t_env	*env;
	bool	print;

	env = (t_env *)data;
	print = true;
	while (env->philo_died == false)
	{
		if (env->philo_reached_meal_limit == true \
			|| ph_check_if_someone_died(env, print) == true)
			return (NULL);
	}
	return (NULL);
}

int	ph_run_life_monitor(t_env *env)
{
	pthread_t	monitor_tid;

	if (ph_pthread_create(env, &monitor_tid, ph_start_monitor) != SUCCESS)
		return (ERROR);
//pthread_create(&monitor_tid, NULL,&ph_start_monitor, env);

	if (pthread_join(monitor_tid, NULL) != SUCCESS)
	{
		env->errors[5] = true;
		return (ERROR);
	}
	return (SUCCESS);
}
