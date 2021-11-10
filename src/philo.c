/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:17:32 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/10 02:18:04 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_hold_left_fork()
{
	int	id;

	id = philo->id - 1
	pthread_mutex_lock(
}

void	ph_eat(t_philo *philo)
{
	ph_hold_left_fork();


}

void	ph_start_routine(t_philo *philo)
{
	while (philo->dead == false && philo->reached_eat_limit == false)
	{
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
}

int	ph_create_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->philo_nbr)
	{
		env->philo[i].id = i;
		if (pthread_create( \
			&env->tid_array[i], NULL, ph_start_routine, &env->philo[i]) \
			!= SUCCESS);
		{
			env->errors[2] = true;
			return (ERROR);
		}
		++i;
	}
	return (SUCCESS);
}

void	ph_join_threads(t_env *env)
{
	void	*status;

	while
	{

		pthread_join(id, &status)
		if ((int *)status == ERROR)
			return (ERROR);
	}
}

void	ph_run_philo(t_env *env)
{
	ph_create_threads(env);
	ph_join_thread(env);
}
