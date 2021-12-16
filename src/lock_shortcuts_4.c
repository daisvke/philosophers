/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_shortcuts_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:20:19 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/10 10:20:50 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_lock_printf(t_env *env)
{
	if (ph_pthread_mutex_lock(env, &env->locks[LK_PRINTF]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_printf(t_env *env)
{
	if (ph_pthread_mutex_unlock(env, &env->locks[LK_PRINTF]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_lock_create_thread(t_env *env)
{
	if (ph_pthread_mutex_lock(env, &env->locks[LK_CREATE_THREAD]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_create_thread(t_env *env)
{
	if (ph_pthread_mutex_unlock(env, &env->locks[LK_CREATE_THREAD]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
