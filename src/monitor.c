/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:04:34 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/20 22:58:23 by dtanigaw         ###   ########.fr       */
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
		if (env->monitor_on == true)
		{
			if (env->philo_reached_meal_limit)
				printf("npowreachedmeal\n");
			if (env->philo_reached_meal_limit == true \
				|| ph_check_if_someone_died(env, print) == true)
			{
	printf("-----------inside monitor if-------------\nn");
				return (NULL);
			}
		}
	}
	return (NULL);
}

int	ph_run_life_monitor(t_env *env)
{
	if (ph_pthread_create(env, &env->monitor_tid, ph_start_monitor) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
