/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_shortcuts_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 01:17:36 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/10 10:21:46 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_lock_fork(t_env *env, size_t id)
{
	if (ph_pthread_mutex_lock(env, &env->forks[id]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_fork(t_env *env, size_t id)
{
	if (ph_pthread_mutex_unlock(env, &env->forks[id]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_lock_print(t_env *env)
{
	if (ph_pthread_mutex_lock(env, &env->locks[LK_LOCK_PRINT]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_print(t_env *env)
{
	if (ph_pthread_mutex_unlock(env, &env->locks[LK_LOCK_PRINT]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
