/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_shortcuts_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:18:48 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/10 10:19:27 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_lock_philo_died(t_env *env)
{
	if (ph_pthread_mutex_lock(env, &env->locks[LK_PHILO_DIED]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_philo_died(t_env *env)
{
	if (ph_pthread_mutex_unlock(env, &env->locks[LK_PHILO_DIED]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_lock_last_meal_time(t_env *env)
{
	if (ph_pthread_mutex_lock(env, &env->locks[LK_LAST_MEAL_TIME]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_last_meal_time(t_env *env)
{
	if (ph_pthread_mutex_unlock(env, &env->locks[LK_LAST_MEAL_TIME]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
