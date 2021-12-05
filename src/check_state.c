/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:06:04 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/04 08:35:55 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_check_if_philo_has_reached_meal_limit(t_env *env, t_philo *philo)
{
	size_t	limit;

	limit = env->meal_limit;
	if (limit && philo->meal_count >= limit)
	{
		philo->reached_meal_limit = true;
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
	last_meal_time = philo->last_meal_time;
	deadline_to_eat = last_meal_time + time_to_die;
	if (deadline_to_eat > 0 && curr_time > deadline_to_eat)
		return (true);
	return (false);
}
