/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:04:34 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/19 02:17:16 by dtanigaw         ###   ########.fr       */
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

	if (ph_pthread_create(env, monitor_tid, ph_start_monitor) != SUCCESS)
	{
		env->errors[2] = true;
		return (ERROR);
	}
//	if (pthread_detach(monitor_tid) != SUCCESS)
//		return (ERROR);
	return (SUCCESS);
}
