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
	t_philo	*philo;
	bool	print;

	philo = (t_philo *)data;
	printf("-----------start monitor------------id: %ld\n", philo->id);
	env = philo->env;
	while (env->philo_died == false)
	{

		{
			if (philo->monitor_on == true && ph_check_if_philo_died(env, philo) == true)
			{
	printf("-----------inside monitor if-------------id: %ld\n", philo->id);
				return (NULL);
			}
		}
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
		return (ERROR);
	return (SUCCESS);
}
