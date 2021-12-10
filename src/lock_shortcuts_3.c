/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_shortcuts_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:19:38 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/10 10:22:41 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_lock_start_simulation(t_env *env)
{
	if (ph_pthread_mutex_lock(env, &env->locks[LK_START_SIMULATION]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_start_simulation(t_env *env)
{
	if (ph_pthread_mutex_unlock(env, &env->locks[LK_START_SIMULATION]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_lock_reached_meal_limit(t_env *env)
{
	if (ph_pthread_mutex_lock(env, &env->locks[LK_REACHED_MEAL_LIMIT]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_reached_meal_limit(t_env *env)
{
	if (\
		ph_pthread_mutex_unlock(env, &env->locks[LK_REACHED_MEAL_LIMIT]) \
		== ERROR)
		return (ERROR);
	return (SUCCESS);
}
