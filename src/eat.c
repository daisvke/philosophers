/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 05:46:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/10 06:07:18 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_hold_fork(t_env *env, int side)
{
	int	philo_id;
	int	fork_id;

	philo_id = env->curr_id;
	fork_id = philo_id + side;
	if (pthread_mutex_lock(env->forks[fork_id]) != SUCCESS)
	{
		env->errors[3];
		return (ERROR);
	}
}

int	ph_drop_forks(t_env *env)
{
	int	philo_id;
	int	r_fork;
	int	l_fork;

	philo_id = env->curr_id;
	r_fork = philo_id - 1;
	l_fork = philo_id + 1;
	if (pthread_mutex_unlock(env->forks[r_fork]) != SUCCESS \
		|| pthread_mutex_unlock(env->forks[l_fork]) != SUCCESS)
	{
		env->errors[4];
		return (ERROR);
	}
}

int	ph_eat(t_env *env)
{
	if (ph_hold_fork(env, RIGHT) == ERROR \
		|| ph_hold_fork(env, LEFT) == ERROR \
		|| ph_usleep(env->time.eat) == ERROR \
		|| ph_drop_forks(env) == ERROR)
		return (ERROR);
}
