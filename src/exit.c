/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 04:50:26 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/10 01:01:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_destroy_mutex_array(pthread_mutex_t *mutex_arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&mutex_arr[i]);
		++i;
	}
}

void	ph_free_arrays(t_env *env, t_philo *philo_arr)
{
	env->threads = ph_free(env->threads);
	env->forks = ph_free(env->forks);
	philo_arr = ph_free(philo_arr);
}

void	ph_destroy_all_mutex(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < LOCK_NBR)
	{
		if (pthread_mutex_destroy(&env->locks[i]) != SUCCESS)
			env->errors[11] = true;
		++i;
	}
	i = 0;
	while (i < env->philo_nbr)
	{
		if (pthread_mutex_destroy(&env->forks[i]) != SUCCESS)
			env->errors[12] = true;
		++i;
	}
}

void	ph_clean_arrays(t_env *env, t_philo *philo_arr)
{
	ph_destroy_all_mutex(env);
	ph_free_arrays(env, philo_arr);
}
