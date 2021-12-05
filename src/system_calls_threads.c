/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_calls_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 10:30:03 by root              #+#    #+#             */
/*   Updated: 2021/12/05 10:30:42 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_pthread_mutex_init(t_env *env, pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != SUCCESS)
	{
		env->errors[9] = true;
		return (ERROR);
	}
	return (SUCCESS);
}

int	ph_pthread_create(t_env *env, pthread_t *tid, void *(f)(void *), \
	t_philo *philo)
{
	if (pthread_create(\
		tid, NULL, (f), philo) != SUCCESS)
	{
		env->error_occured_on_some_thread = true;
		env->errors[2] = true;
		return (ERROR);
	}
	return (SUCCESS);
}

int	ph_pthread_join(t_env *env, pthread_t tid)
{
	if (pthread_join(tid, NULL) != SUCCESS)
	{
		env->error_occured_on_some_thread = true;
		env->errors[5] = true;
		return (ERROR);
	}
	return (SUCCESS);
}

int	ph_pthread_mutex_lock(t_env *env, pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != SUCCESS)
	{
		env->error_occured_on_some_thread = true;
		env->errors[3] = true;
		return (ERROR);
	}
	return (SUCCESS);
}

int	ph_pthread_mutex_unlock(t_env *env, pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != SUCCESS)
	{
		env->error_occured_on_some_thread = true;
		env->errors[4] = true;
		return (ERROR);
	}
	return (SUCCESS);
}
