/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:04:34 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/18 06:17:40 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_start_monitor(t_env *env)
{
	bool	print;

	print = true;
	while (env->philo_died == false)
	{
		if (env->philo_reached_meal_limit == true \
			|| ph_check_if_someone_died(env, print) == true)
			return (NULL);
	}
}

int	ph_run_life_monitor(t_env *env)
{
	if (ph_pthread_create( \
		env, monitor_tid, NULL, ph_start_monitor, env) != SUCCESS)
		return (ERROR);
	if (pthread_detach(monitor_tid) != SUCCESS)
		return (ERROR);
}
