/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:06:04 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/10 02:10:30 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_check_if_philo_has_reached_meal_limit(t_env *env, t_philo *philo)
{
	size_t	limit;

	limit = env->meal_limit;
	if (limit && philo->meal_count >= limit)
	{
		ph_lock_reached_meal_limit(env);
		philo->reached_meal_limit = true;
		ph_unlock_reached_meal_limit(env);
		return (true);
	}
	return (false);
}

bool	ph_is_dead(t_env *env, t_philo *philo)
{
	size_t	time_to_die;
	size_t	curr_time;
	size_t	deadline_to_eat;
	size_t	last_meal_time;

	time_to_die = env->time.die * 1000;
	if (ph_gettime(env, &curr_time) == ERROR)
		return (true);
	ph_lock_last_meal_time(env);
	last_meal_time = philo->last_meal_time;
	ph_unlock_last_meal_time(env);
	deadline_to_eat = last_meal_time + time_to_die;
	if (deadline_to_eat > 0 && curr_time > deadline_to_eat)
		return (true);
	return (false);
}
