/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:06:04 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/04 02:50:27 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_check_if_philo_has_reached_meal_limit(t_env *env, t_philo *philo)
{
	size_t	limit;

	limit = env->meal_limit;
	if (limit && philo->meal_count == limit)
	{
		env->philo_reached_meal_limit = true;
		printf("reached limit\n");
		return (true);
	}
	return (false);
}

bool	ph_is_dead(t_env *env, t_philo *philo)
{
	size_t	time_to_die;
	size_t	curr_time;
	size_t	time_diff;
	size_t	deadline_to_eat;
	size_t	last_meal_time;

	time_to_die = env->time.die * 1000;
	if (ph_gettime(env, &curr_time) == ERROR)
		return (true);
//	deadline_to_eat = (curr_time / 1000) - time_to_eat;
	last_meal_time = philo->last_meal_time;
	deadline_to_eat = last_meal_time + time_to_die;
//		printf("philo%d lastmealtime:%ld\n", philo->id, last_meal_time);
	if (deadline_to_eat > 0 && curr_time > deadline_to_eat)
	{
printf("deadlineto_eat: %ld\n" , deadline_to_eat);
printf("die time: %ld\n" , time_to_die);
printf("curr time: %ld\n" , curr_time);
		printf("philo%d lastmealtime:%ld\n", philo->id, last_meal_time);
		philo->is_dead = true;
		return (true);
	}
	return (false);
}
