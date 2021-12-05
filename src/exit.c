/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 04:50:26 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/18 21:25:50 by dtanigaw         ###   ########.fr       */
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

